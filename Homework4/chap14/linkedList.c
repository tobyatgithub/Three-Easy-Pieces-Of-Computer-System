#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(int argc, char const *argv[])
{
    /* code */
    printf("ok\n");

    int *data = (int *) malloc(sizeof(int));
    struct vector v = {.data = data, .size=0, .capacity=1};
    struct vector *p = &v;

    for (int i = 0; i < 5; i++)
    {
        /* code */
        printf("push back value %d into vector p...\n", i);
        push_back(p, i);
        printf("check: the %dth value in vector v is: %d\n\n", i, v.data[i]);
    }

    for (int i = 4; i >= 0; i--)
    {
        printf("%d\n", v.data[i]);
        pop_back(p);
        printf("size: %d\n", v.size);
        printf("capacity: %d\n", v.capacity);

    }
    

    return 0;
}
