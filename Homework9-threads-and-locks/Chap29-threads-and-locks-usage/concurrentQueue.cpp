//
// Created by tobyf on 11/24/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct __node_t {
    int key;
    struct __node_t *next;
} node_t;

typedef struct __queue_t {
    node_t *head;
    node_t *tail;
    pthread_mutex_t headLock;
    pthread_mutex_t tailLock;
} queue_t;

void Queue_Init(queue_t *Q) {
    node_t *tmp = static_cast<node_t *>(malloc(sizeof(node_t)));
    tmp->next = NULL;
    Q->head = Q->tail = tmp;
    pthread_mutex_init(&Q->headLock, NULL);
    pthread_mutex_init(&Q->tailLock, NULL);
}

void Queue_Enqueue(queue_t *Q, int key) {
    node_t *tmp = static_cast<node_t *>(malloc(sizeof(node_t)));
    tmp->key = key;
    tmp->next = NULL;

    pthread_mutex_lock(&Q->tailLock);
    Q->tail->next = tmp;
    Q->tail = tmp;
    pthread_mutex_unlock(&Q->tailLock);
}

int Queue_Dequeue(queue_t *Q) {
    pthread_mutex_lock(&Q->headLock);
    node_t *tmp = Q->head;
    node_t *newHead = tmp->next;
    if (newHead == NULL) {
        perror("Queue was empty");
        pthread_mutex_unlock(&Q->headLock);
        return -1;
    }
    newHead = newHead->next;
    Q->head = newHead;
    pthread_mutex_unlock(&Q->headLock);
    free(tmp);
    return 0;
}

void Queue_Print(queue_t *Q) {
    node_t *cur = Q->head;
    while (cur) {
        printf("%d\n", cur->key);
        cur = cur->next;
    }
}

int main() {
    queue_t *Q = static_cast<queue_t *>(malloc(sizeof(queue_t)));
    Queue_Init(Q);
    Queue_Enqueue(Q, 0);
    Queue_Enqueue(Q, 1);
    Queue_Enqueue(Q, 2);
    Queue_Enqueue(Q, 3);
    Queue_Dequeue(Q);
    Queue_Print(Q);
    printf("\n");
    Queue_Enqueue(Q, 4);
    Queue_Enqueue(Q, 5);
    Queue_Dequeue(Q);
    Queue_Print(Q);
    pthread_mutex_destroy(&Q->headLock);
    pthread_mutex_destroy(&Q->tailLock);
    free(Q);
    return 0;
}