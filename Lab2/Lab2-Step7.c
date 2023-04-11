/*
Name: Maddie Waldie
Date: 4/12
Title: Lab2 – Step 7: Rewrite the program in Step 1, so that 
the child process runs the ls command and the parent
process waits until the child process terminates before it exits. 
Description: This program demonstrates the use of fork().
*/

/* C program to demonstrate the use of fork()*/
#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */

/* main function */
int main() {
    pid_t pid;
    int i, n = 3000; // n is a delay in microseconds inserted in parent and child iterations
    printf("\n Before forking.\n");
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }
    if (pid){
        // Parent process: pid is > 0
        wait(0);
        printf("\n Child has completed the task! \n");
        exit(0);
    }
    else{
        // Child process: pid = 0
        execlp("/bin/ls", "ls", "-l", 0);
    }
    return 0;
}