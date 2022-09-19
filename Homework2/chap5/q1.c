#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int)getpid());
    int rc = fork();
    int x = 100;
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        printf("hello, i am child (pid%d)\n", (int)getpid());
        printf("child: value of x = (%d)\n", (int)x);
        x = 101;
        printf("child: change x to 101, x = (%d)\n", (int)x);
    }
    else
    {
        printf("hello, i am parent of %d (pid:%d)\n", rc, (int)getpid());
        printf("parent: value of x = (%d)\n", (int)x);
        x = 1010;
        printf("parent: change x to 1010, x = (%d)\n", (int)x);
    }
    return 0;
}