// Name: Maddie Waldie
// Date: 4/26/23
// Title: Lab4 – Step 1
// Description: 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *go(void *);
#define NTHREADS 20
pthread_t threads[NTHREADS];

int main() {
    int i;

    for (i = 0; i < NTHREADS; i++) {
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    }
    printf("Main thread done.\n");
    return 0;
}

void *go(void *arg) {
    printf("Hello from thread %d with iteration %d\n", (int)(unsigned long)pthread_self(), (int)(unsigned long)(size_t *)arg);
    sleep(15);
    pthread_exit(0);
}