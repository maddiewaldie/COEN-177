// Name: Maddie Waldie
// Date: 5/3/23
// Title: Lab5 – Step 4
// Description: Write a program that solves the producer-consumer problem using semaphores.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <fcntl.h>

#define NTHREADS 10
#define n 10

// Variable declaration
pthread_t threads[NTHREADS];
int buffers[n];
int add_index, remove_index;
sem_t *full, *empty, *mutex; 

void cleanup(int sigtype){
    sem_unlink("full"); 
    sem_unlink("empty"); 
    sem_unlink("mutex"); 
    printf("\n Terminating\n");
    exit(0);
}

void* producer() { 
    int added_item;
    do {
        // produce next item between 0-1
        added_item = rand() % 100;

        // entry section
        sem_wait(empty);
        sem_wait(mutex);

        // add item to buffer
        buffers[add_index] = added_item;
        printf("%d added to index %d\n", added_item, add_index);
        add_index = (add_index + 1) % n; // increment index circularly

        // exit section
        sem_post(mutex);
        sem_post(full);
    } while(1);
} 

void* consumer() { 
    int removed_item;
    do {
        // entry section
        sem_wait(full);
        sem_wait(mutex);

        // remove next item from buffer
        removed_item = buffers[remove_index];
        printf("%d removed from index %d\n", removed_item, remove_index);
        remove_index = (remove_index + 1) % n; // increment index circularly
        
        // exit section
        sem_post(mutex);
        sem_post(empty);
    } while(1);
} 

int main() { 
    signal(SIGINT,cleanup);
    full = sem_open("full", O_CREAT, 0644, 0);
    empty = sem_open("empty", O_CREAT, 0644, n);
    mutex = sem_open("mutex", O_CREAT, 0644, 1);

    static int i;
    add_index = 0;
    remove_index = 0;

    // Create threads
    for (i = 0; i < NTHREADS/2; i++)  
        pthread_create(&threads[i], NULL, producer, NULL);
    for (i = NTHREADS/2; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, consumer, NULL);

    // Join threads
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i],NULL);
    }
    printf("Main thread done.\n");

    sem_unlink("full"); 
    sem_unlink("empty"); 
    sem_unlink("mutex"); 
    return 0; 
} 