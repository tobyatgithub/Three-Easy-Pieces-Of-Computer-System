

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd;
    char s;
    FILE *file;
    FILE *f;
    fd = open("open.txt", O_RDONLY);
    file = fopen("open.txt", "w");
    printf("%d \n", fd);
    int rc = fork();

    if (rc == -1)
    {
        printf("Fork failed");
        exit(1);
    }
    else if (rc == 0)
    {
        int num = 1010;
        fprintf(file, "%d", num);
        printf("For the child process, fd == %d \n", fd);
        fclose(file);
        f = fopen("open.txt", "r");
        while ((s = fgetc(f)) != EOF)
        {
            printf("%c", s);
        }
        printf("\n");
    }
    else
    {
        int num = 2020;
        fprintf(file, "%d", num);
        printf("For the parent process, fp == %d \n", fd);
        fclose(file);
        f = fopen("open.txt", "r");
        while ((s = fgetc(f)) != EOF)
        {
            printf("%c", s);
        }
        printf("\n");
    }
    return 0;
}