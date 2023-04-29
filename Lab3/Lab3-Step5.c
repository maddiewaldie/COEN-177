// Name: Maddie Waldie
// Date: 4/19/23
// Title: Lab3 – Step
// Description: Implements the producer-consumer message communication using pipes

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>

// main
int main(int argc, char *argv[])
{
    int fds[2];
    char buff[60];
    int count;
    int i;
    pipe(fds);

    if (fork() == 0)
    {
        printf("\nWriter on the upstream end of the pipe -> %d arguments \n", argc);
        close(fds[0]);
        scanf("%s", buff);
        write(fds[1], buff, strlen(buff));
        exit(0);
    }
    else if (fork() == 0)
    {
        printf("\nReader on the downstream end of the pipe \n");
        close(fds[1]);
        while ((count = read(fds[0], buff, 60)) > 0)
        {
            printf("buff: %s\n", buff);
        }
        exit(0);
    }
    else
    {
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}