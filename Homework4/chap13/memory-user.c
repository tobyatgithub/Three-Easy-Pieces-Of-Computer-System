#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n[1000000];
    int i;

    while (1)
    {
        for (i = 0; i < 1000000; i++) {
            n[i] = i + 100;
            // printf("running");
        }
        /* code */
    }
    
    return 0;
}

/* 
While running:
              total        used        free      shared  buff/cache   available
Mem:          15929         864       13790           0        1273       14786
Swap:          4096           0        4096

While not running:
              total        used        free      shared  buff/cache   available
Mem:          15929         861       13794           0        1273       14789
Swap:          4096           0        4096

 */