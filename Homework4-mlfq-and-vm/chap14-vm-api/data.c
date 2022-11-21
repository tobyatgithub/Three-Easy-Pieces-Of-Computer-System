#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array = (int*) malloc(sizeof(int) * 100);
    array[100] = 0;
    return 0;
}