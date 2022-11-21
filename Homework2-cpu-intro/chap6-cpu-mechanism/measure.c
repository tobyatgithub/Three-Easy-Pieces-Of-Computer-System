#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int main()
{
    FILE *ptr;
    int FACTOR = 1;
    struct timeval start, end;

    gettimeofday(&start, NULL);
    for (int i = 0; i < 5; i++)
    {
        ptr = fopen("hello.txt", "r");
        sleep(1);
    }
    gettimeofday(&end, NULL);

    printf("end == %ld\n", end.tv_sec * FACTOR);
    printf("start == %ld\n", start.tv_sec * FACTOR);
    return 0;
}