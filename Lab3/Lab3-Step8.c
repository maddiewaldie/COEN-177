// Name: Maddie Waldie
// Date: 4/19/23
// Title: Lab3 – Step
// Description: Creates threads and prints when the threads are iterating / done / returned.
// Instructions: What is the fix for the program bug in Step 7? Then write a program to demonstrate your f

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];
int main() {
    int i;
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    for (i = 0; i < NTHREADS; i++) {
    printf("Thread %d returned\n", i);
        pthread_join(threads[i],NULL);
    }
    printf("Main thread done.\n");
    return 0;
}

void *go(void *arg) {
    printf("Hello from thread %d with iteration %d\n",  (int)(unsigned long) pthread_self(), (size_t *)(int)arg);
    return 0;
}