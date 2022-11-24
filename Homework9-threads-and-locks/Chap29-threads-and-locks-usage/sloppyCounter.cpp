//
// Created by tobyf on 11/24/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define ONE_MILLION 100000
#define NUMCPUS 4


typedef struct __counter_t {
    int global;
    pthread_mutex_t glock;
    int local[NUMCPUS];
    pthread_mutex_t llock[NUMCPUS];
    int threshold;
} counter_t;

typedef struct __myarg_t {
    counter_t *c;
    int threshold;
    int amt;
    int threads;
    char pad[sizeof(counter_t *) - sizeof(int)];
} myarg_t;

void init(counter_t *c, int threshold) {
    c->global = 0;
    c->threshold = threshold;
    pthread_mutex_init(&c->glock, NULL);
    for (int i = 0; i < NUMCPUS; i++) {
        c->local[i] = 0;
        pthread_mutex_init(&c->llock[i], NULL);
    }
}

void increment(counter_t *c, int threadID, int amt) {
    int cpu = threadID % NUMCPUS;
    pthread_mutex_lock(&c->llock[cpu]);

    c->local[cpu] += amt;

    if (c->local[cpu] >= c->threshold) {
        pthread_mutex_lock(&c->glock);
        c->global += c->local[cpu];
        pthread_mutex_unlock(&c->glock);
        c->local[cpu] = 0;
    }
    pthread_mutex_unlock(&c->llock[cpu]);
}


int get(counter_t *c) {
    pthread_mutex_lock(&c->glock);
    int i = c->global;
    pthread_mutex_unlock(&c->glock);
    return i;
}

void *threadFunction(void *args) {
    myarg_t *m = static_cast<myarg_t *>(args);
    for (int i = 0; i < ONE_MILLION; i++)
        increment(m->c, m->threads, m->amt);
    pthread_exit(0);

    return (void *) 1;
}

int main() {
    for (int numThreads = 1; numThreads < 6; numThreads++) {
        double threshold = pow(2.0, (double) numThreads);
        for (int j = 1; j <= NUMCPUS; j++) {
            counter_t *c = static_cast<counter_t *>(malloc(sizeof(counter_t)));
            init(c, (int) threshold);
            pthread_t *threads = static_cast<pthread_t *>(malloc((size_t) j * sizeof(pthread_t)));
            myarg_t args;
            args.c = c;
            args.threshold = (int) threshold;
            args.amt = 1;
            args.threads = j;
            struct timeval start, end;
            gettimeofday(&start, NULL);
            for (int k = 0; k < j; k++)
                pthread_create(&threads[k], NULL, &threadFunction, &args);
            for (int l = 0; l < j; l++)
                pthread_join(threads[l], NULL);
            gettimeofday(&end, NULL);

            long long startusec, endusec;
            startusec = start.tv_sec * ONE_MILLION + start.tv_usec;
            endusec = end.tv_sec * ONE_MILLION + end.tv_usec;
            printf("%d threads, %d threshold\n", j, (int) threshold);
            printf("%d global counter\n", get(c));
            printf("Time (seconds): %f\n\n",
                   ((double) (endusec - startusec) / ONE_MILLION));
            pthread_mutex_destroy(&c->glock);
            for (int m = 0; m < NUMCPUS; m++)
                pthread_mutex_destroy(&c->llock[m]);
            free(c);
            free(threads);
        }
    }

    return 1;
};