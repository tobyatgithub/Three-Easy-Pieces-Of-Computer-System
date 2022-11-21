#include <stdio.h>  /* for printf */
#include <stdlib.h> // exit, calloc, free
#include <time.h>   /* for clock_gettime */
#include <unistd.h>

int main(int argc, char **argv)
{
    // uint64_t execTime; /*time in nanoseconds */
    // struct timespec tick, tock;
    // clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tick);
    // /* do stuff */
    // sleep(2);
    // clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tock);
    // execTime = 1E9 * (tock.tv_sec - tick.tv_sec) + tock.tv_nsec - tick.tv_nsec;
    // printf("elapsed process CPU time = %llu nanoseconds\n", (long long unsigned int)execTime);

    if (argc < 2)
    {
        fprintf(stderr, "Expected 2 arguments but got fewer.\n");
        exit(EXIT_FAILURE);
    }

    long PAGESIZE = sysconf(_SC_PAGESIZE);
    long jump = PAGESIZE / sizeof(int);
    int pages = atoi(argv[1]);
    int epochs = atoi(argv[2]);
    printf("Executing, PAGESIZE = %ld, jump = %ld, page = %d, epochs = %d\n", PAGESIZE, jump, pages, epochs);
    if (pages <= 0 || epochs <= 0)
    {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }

    int *a = calloc(pages, PAGESIZE);
    struct timespec start, end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for (int j = 0; j < epochs; j++)
    {
        for (int i = 0; i < jump * pages; i += jump)
        {
            a[i] += 1;
        }
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    int execTime = 1E9 * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("Average elapsed = %d nanosecond per epochs page.\n", (execTime / (epochs * pages)));
    free(a);
    return 0;
}