#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *p = (int *)calloc(1, sizeof(int));
    p = NULL;
    printf("%d\n", *p);
    free(p);
    return 0;
}