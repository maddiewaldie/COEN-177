/*
Name: Maddie Waldie
Date: 4/12
Title: Lab2 – Step 6: Write a C program to create 5 processes 
(including the initial program itself – parent) so that
each process iterates with a different delay taken as a command-line 
argument. In this case, you will have 5 command-line arguments. 
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
    pid_t pid1, pid2, pid3;
    if (argc != 6) {
        printf("Usage: %s <delay1> <delay2> <delay3> <delay4> <delay5> \n", argv[0]);
        exit(0);
    }
    int i, n1 = atoi(argv[1]), n2 = atoi(argv[2]), n3 = atoi(argv[3]), n4 = atoi(argv[4]), n5 = atoi(argv[5]); // n microseconds is taken as command-line argument
    printf("\n Before forking.\n");
    pid1 = fork();
    pid2 = fork();
    if (pid1 < 0 || pid2 < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }
    if (pid1 > 0 && pid2 > 0){
        pid3 = fork();
        if (pid3 > 0) {
            for (i=0;i<10;i++) {
                printf("\t I am the process (PID: %d) displaying iteration %d \n", getpid(), i);
                usleep(n1);
            }
        }
        else if (pid3 == 0) {
            for (i=0;i<10;i++) {
                printf("\t I am the process (PID: %d) displaying iteration %d \n", getpid(), i);
                usleep(n2);
            }
        }
    }
    else if (pid1 > 0 && pid2 == 0) {
        for (i=0;i<10;i++) {
            printf("\t \t I am the process (PID: %d) displaying iteration %d \n", getpid(), i);
            usleep(n3);
        }
    }
    else if (pid1 == 0 && pid2 > 0) {
        for (i=0;i<10;i++) {
            printf("\t \t \t I am the process (PID: %d) displaying iteration %d \n", getpid(), i);
            usleep(n4);
        }
    }
    else {
        for (i=0;i<10;i++) {
            printf("\t \t \t  \t I am the process (PID: %d) displaying iteration %d \n", getpid(), i);
            usleep(n5);
        }
    }
    return 0;
}