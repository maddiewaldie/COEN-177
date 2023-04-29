/*
Name: Maddie Waldie
Date: 4/12
Title: Lab2 – Step 3: Rewrite the program in Step 1 so that the delay is 
determined by the user entered as a command line argument.
Description: This program demonstrates the use of fork().
*/

/* C program to demonstrate the use of fork()*/
#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */

/* main function */
int main(int argc, char *argv[]) {
    pid_t pid;
    if (argc != 2) {
        printf("Usage: %s <delay> \n", argv[0]);
        exit(0);
    }
    int i, n = atoi(argv[1]); // n microseconds is taken as command-line argument
    printf("\n Before forking.\n");
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }
    if (pid){
        // Parent process: pid is > 0
        for (i=0;i<10;i++) {
            printf("\t \t \t I am the parent process (PID: %d) displaying iteration %d \n", getpid(), i);
            usleep(n);
        }
    }
    else{
        // Child process: pid = 0
        for (i=0;i<10;i++) {
            printf("I am the child process (PID: %d) displaying iteration %d\n", getpid(),i);
            usleep(n);
        }
    }
    return 0;
}