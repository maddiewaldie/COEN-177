// Name: Maddie Waldie
// Date: 5/3/23
// Title: Lab5 – Step 5
// Description: Write a program that solves the producer-consumer problem using condition variables

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
pthread_mutex_t mute_x;
pthread_cond_t full, empty;
int size;

void* producer() { 
    int added_item;
    do {
        // produce next item between 0-1
        added_item = rand() % 100;

        // entry section
        pthread_mutex_lock(&mute_x);

        // while the buffer is full, wait
        while (size == n)
            pthread_cond_wait(&empty, &mute_x);

        // add item to buffer
        buffers[add_index] = added_item;
        printf("%d added to index %d\n", added_item, add_index);
        add_index = (add_index + 1) % n; // increment index circularly
        size++;

        // exit section
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mute_x);
    } while(1);
} 

void* consumer() { 
    int removed_item;
    do {
        // entry section
        pthread_mutex_lock(&mute_x);

        // while the buffer is empty, wait
        while(size == 0)
            pthread_cond_wait(&full, &mute_x);

        // remove next item from buffer
        removed_item = buffers[remove_index];
        printf("%d removed from index %d\n", removed_item, remove_index);
        remove_index = (remove_index + 1) % n; // increment index circularly
        size--;
        
        // exit section
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mute_x);
    } while(1);
} 

int main() { 
    pthread_mutex_init(&mute_x, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&full, NULL);

    static int i;
    add_index = 0;
    remove_index = 0;
    size = 0;

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

    pthread_mutex_destroy(&mute_x);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);
    return 0; 
} 