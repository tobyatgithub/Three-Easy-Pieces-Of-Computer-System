#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array = (int*) malloc(sizeof(int) * 100);
    free(&array[10]); // aborted invalid pointer
    return 0;
}