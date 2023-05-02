// Name: Maddie Waldie
// Date: 5/3/23
// Title: Lab5 – Step 3
// Description: Modify threadSync.c in Step 2 using mutex Locks

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h> 
#include <unistd.h>


#define NTHREADS 10

void *go(void *arg);
//void cleanup(int sigtype);

pthread_t threads[NTHREADS];
pthread_mutex_t lock;

int main() {
    //signal(SIGINT,cleanup);
    pthread_mutex_init(&lock, NULL); // create a lock
    static int i;
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i],NULL);
        printf("\t\t\tThread %d returned \n", i);
    }
    printf("Main thread done.\n");
    pthread_mutex_destroy(&lock); // delete lock
    return 0; 
}

void *go(void *arg) {
    pthread_mutex_lock(&lock); // lock acquire; entry section
    printf("Thread %d Entered Critical Section..\n", (int)arg); // critical section 
    sleep(1); 
    pthread_mutex_unlock(&lock); // lock release; exit section
    return (NULL);
}

/*void cleanup(int sigtype){
    sem_unlink("mutex");
    printf("\n Terminating\n");
    exit(0);
}*/