//
// Created by tobyf on 11/24/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#define ONE_MILLION 100000

typedef struct __node_t {
    int key;
    struct __node_t *next;
} node_t;

typedef struct __list_t {
    node_t *head;
    pthread_mutex_t lock;
} list_t;

void List_Init(list_t *L) {
    L->head = NULL;
    pthread_mutex_init(&L->lock, NULL);
}

void List_Insert(list_t *L, int key) {

    node_t *newNode = static_cast<node_t *>(malloc(sizeof(node_t)));
    if (newNode == NULL) {
        perror("malloc");
        return;
    }
    newNode->key = key;

    pthread_mutex_lock(&L->lock);
    newNode->next = L->head;
    L->head = newNode;
    pthread_mutex_unlock(&L->lock);
}

int List_Lookup(list_t *L, int key) {
    int rv = -1;
    pthread_mutex_lock(&L->lock);
    node_t *cur = L->head;
    while (cur) {
        if (cur->key == key) {
            rv = 0;
            break;
        }
        cur = cur->next;
    }
    pthread_mutex_unlock(&L->lock);
    return rv;
}

void List_Print(list_t *L) {
    // probably dont need a lock for read
    node_t *cur = L->head;
    while (cur) {
        printf("%d\n", cur->key);
        cur = cur->next;
    }
}

void List_Free(list_t *L) {
    pthread_mutex_lock(&L->lock);
    node_t *cur = L->head;
    while (cur) {
        node_t *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    pthread_mutex_unlock(&L->lock);
    free(L);
}

void *thread_function(void *args) {
    list_t *l = (list_t *) args;
    List_Lookup(l, 0);
    /* printf("Search key 0: %d\n", List_Lookup(l, 0)); */
    pthread_exit(EXIT_SUCCESS);
}

int main() {

    int list_length = 100;
    int thread_count = 10;
    int print = false;

    list_t *list = static_cast<list_t *>(malloc(sizeof(list_t)));
    List_Init(list);

    for (int i = 0; i < list_length; i++)
        List_Insert(list, i);

    for (int i = 1; i <= thread_count; i++) {
        int s = 0;
        struct timeval start, end;
        s = gettimeofday(&start, NULL);


        pthread_t *threads = static_cast<pthread_t *>(malloc((size_t) i * sizeof(pthread_t)));


        for (int j = 0; j < i; j++)
            pthread_create(&threads[j], NULL, &thread_function, list);
        for (int k = 0; k < i; k++)
            pthread_join(threads[k], NULL);

        s = gettimeofday(&end, NULL);
        long long startusec, endusec;
        startusec = start.tv_sec * ONE_MILLION + start.tv_usec;
        endusec = end.tv_sec * ONE_MILLION + end.tv_usec;
        if (print)
            List_Print(list);
        printf("%d threads, time (seconds): %f\n\n", i,
               ((double) (endusec - startusec) / ONE_MILLION));
        free(threads);
    }

    List_Free(list);

    return 0;
}