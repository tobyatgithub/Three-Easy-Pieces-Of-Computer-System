#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int pid1;
    int pid2;
    int stats;
    printf("hello world (pid:%d)\n", (int)getpid());
    pid1 = fork();
    pid2 = fork();
    if (pid1 < 0)
    {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (pid1 == 0)
    {
        // child (new process)
        printf("hello, I am child1 (pid:%d)\n", (int)getpid());
    }
    else
    {
        // parent goes down this path (original process)
        int wc = waitpid(pid1, &stats, 0);
        printf("hello, I am parent of %d (pid:%d)\n",
               pid1, (int)getpid());
        printf("parent: return of wait = %d\n", wc);
    }

    if (pid2 == 0)
    {
        // child (new process)
        printf("hello, I am child2 (pid:%d)\n", (int)getpid());
    }
    else
    {
        // parent goes down this path (original process)
        // int wc = waitpid(pid1, &stats, 0);
        printf("hello, I am parent of %d (pid:%d)\n",
               pid2, (int)getpid());
        // printf("parent: return of wait = %d\n", wc);
    }
    return 0;
}