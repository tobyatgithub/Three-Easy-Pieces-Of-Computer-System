//
// Created by tobyf on 11/24/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define ONE_MILLION 100000

typedef struct __counter_t{
    int value;
    pthread_mutex_t lock;
} counter_t;

void init(counter_t* c) {
    c->value = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t* c) {
    pthread_mutex_lock(&c -> lock);
    c->value++;
    pthread_mutex_unlock(&c -> lock);
}

void decrement(counter_t* c) {
    pthread_mutex_lock(&c -> lock);
    c->value--;
    pthread_mutex_unlock(&c -> lock);
}

int get(counter_t* c) {
    pthread_mutex_lock(&c -> lock);
    int rc = c-> value;
    pthread_mutex_unlock(&c -> lock);

    return rc;
}

void *threadFunction(void* args) {
    counter_t* c = (counter_t *) args;
    increment(c);
    return (void *) 1;
}

int main() {
    pthread_t p1, p2;
    counter_t* c  = static_cast<counter_t *>(malloc(sizeof(counter_t)));
    init(c);
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i =0 ; i < 10000; i ++) {
        pthread_create(&p1, NULL, threadFunction, c);
        pthread_create(&p2, NULL, threadFunction, c);
        pthread_join(p1, NULL);
        pthread_join(p2, NULL);
    }
    gettimeofday(&end, NULL);

    long long startusec, endusec;
    startusec = start.tv_sec * ONE_MILLION + start.tv_usec;
    endusec = end.tv_sec * ONE_MILLION + end.tv_usec;
    printf("Time (seconds): %f\n\n",
           ((double)(endusec - startusec) / ONE_MILLION));
    printf("%d\n", get(c));


    pthread_t p3, p4, p5, p6;
    struct timeval start2, end2;
    gettimeofday(&start2, NULL);
    for (int i =0 ; i < 5000; i ++) {
        pthread_create(&p3, NULL, threadFunction, c);
        pthread_create(&p4, NULL, threadFunction, c);
        pthread_create(&p5, NULL, threadFunction, c);
        pthread_create(&p6, NULL, threadFunction, c);
        pthread_join(p3, NULL);
        pthread_join(p4, NULL);
        pthread_join(p5, NULL);
        pthread_join(p6, NULL);
    }

    gettimeofday(&end2, NULL); // strange as recall gettimeofday on start and end will result wrong number
    startusec = start2.tv_sec * ONE_MILLION + start2.tv_usec;
    endusec = end2.tv_sec * ONE_MILLION + end2.tv_usec;
    printf("Time (seconds): %f\n\n",
           ((double)(endusec - startusec) / ONE_MILLION));
    printf("%d\n", get(c));

    free(c);
    return 1;
};