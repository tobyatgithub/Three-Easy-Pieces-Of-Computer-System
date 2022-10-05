#include <stdio.h>
#include <stdlib.h>

struct vector
{
    int *data;
    int size;
    int capacity;

};

void push_back(struct vector *vec, int value) {
    if (vec -> size + 1 == vec -> capacity) {
        vec -> capacity = vec -> capacity * 2;
        vec -> data = (int *) realloc(vec -> data, vec -> capacity * sizeof(int));
    }
    vec -> data[vec -> size] =value;
    ++vec -> size;
}

void pop_back(struct vector *vec) {
    --vec -> size;
    vec -> data[vec->size] = 0;
}

void vector_free(struct vector *vec) {
    free(vec -> data);
    vec -> size = 0;
    vec -> capacity = 0;
}