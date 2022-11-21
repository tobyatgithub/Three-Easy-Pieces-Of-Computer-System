#include <stdio.h>

#include "common_threads.h"

int balance = 0;
pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
void* worker(void* arg) {
//    pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;
    Pthread_mutex_lock(&lock1);
    balance++; // unprotected access
    Pthread_mutex_unlock(&lock1);
    return NULL;
}

int main(int argc, char *argv[]) {

    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
    Pthread_mutex_lock(&lock1);
    balance++; // unprotected access
    Pthread_mutex_unlock(&lock1);
    Pthread_join(p, NULL);
    return 0;
}
