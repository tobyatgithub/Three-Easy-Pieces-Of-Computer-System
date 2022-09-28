#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int)getpid());
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc != 0) // parent
    {
        wait(NULL); // sleep(1); or do some heavy work
        printf("hello, i am parent of %d (pid:%d)\n", rc, (int)getpid());
        printf("parent: goodbye.\n");
    }
    else
    {
        printf("hello, i am child (pid%d)\n", (int)getpid());
        printf("child: hello\n");
    }
    return 0;
}