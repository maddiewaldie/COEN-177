/*
Name: Maddie Waldie
Date: 4/12
Title: Lab2 – Step 3: Rewrite the program in Step 3 
with two threads instead of two processes. 
*/

/* C program to demonstrate the use of fork()*/
#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */
#include <pthread.h>

int n_threads = 2, n;

void *thread_function(void *thread_id) {
    int i, tid;
    tid = (int)(unsigned long) (size_t *)thread_id;
    for (i=0;i<10;i++) {
        if(tid) {
            printf("\t \t \t ");
        }
        printf("I am thread %d displaying iteration %d \n", tid, i);
    }
    return thread_id;
}

/* main function */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <delay> \n", argv[0]);
        exit(0);
    }
    int i, th_return;
    pthread_t threads[n_threads];
    
    n = atoi(argv[1]); // n microseconds is taken as command-line argument
    printf("\n Before threading.\n");

    // Creating threads
    for (i=0; i<n_threads; i++) {
        printf("Creating thread %d \n", i);
        pthread_create(&threads[i], NULL, thread_function, (void *)(size_t)i);
    }

    // Joining threads
    for (i=0; i<n_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}