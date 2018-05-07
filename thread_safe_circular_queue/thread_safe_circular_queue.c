#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define SIZE 100

/* ------------- Initialize pthread ------------- */
pthread_mutex_t mutex;
pthread_cond_t cond_var[2];
pthread_t threadID[SIZE];

// Initialize fixed-size array
int array[SIZE];
int front = -1, rear =-1;

/* ------------- Auxiliary queue functions ------------- */
int isFull() {
    if (front == (rear+1)%SIZE) return 1;
    return 0;
}

int isEmpty() {
    if(front == -1) return 1;
    return 0;
}

/* ------------- Add function ------------- */
void add(int element) {
    // Lock the mutex first
    pthread_mutex_lock (&mutex);
    
    if(isFull()) { 
        printf("\nQueue is full. \n");
        // Wait for signal containing cond_var[0]
        pthread_cond_wait(&cond_var[0], &mutex);
    }
    else {
        if(front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        array[rear] = element;
        printf("\nInserted %d", element);
        
    }
    
    // Unlock the mutex
    pthread_mutex_unlock (&mutex);
    // Send the signal that it is done adding
    pthread_cond_signal(&cond_var[1]);
}

/*------------- Remove function ------------- */
int remove_from_queue() {
    int element;

    // Lock the mutex first
    pthread_mutex_lock (&mutex);
    
    if(isEmpty()) {
        printf("\nQueue is empty. \n");
        // Wait for signal containing cond_var[1]
        pthread_cond_wait(&cond_var[1], &mutex);
    } else {        
        element = array[front];
        if (front == rear){
            front = -1;
            rear = -1;
        }
        else {
            front = (front + 1) % SIZE;   
        }
        printf("\nDeleted %d \n", element);
        
        // Unlock the mutex
        pthread_mutex_unlock (&mutex);
        // Send the signal that it is done removing
        pthread_cond_signal(&cond_var[0]);
        return(element);
    }
    return 0;
}

/*------------- Peek function ------------- */
/* Does not need any locks since it is not modifying any data */
void peek() {
    if(isEmpty()) printf(" \n Queue is empty. \n");
    else {
        printf("\nPeek at front: %d\n",front);
    }
}

/*------------- main function ------------- */
int main() {
    int i;
    
    // Initialize threads
    /*
    pthread_t threadID[30];
    pthread_mutex_init (&mutex, NULL);
    */
    // Insert a series of ints
    for(i=0; i<20; i++){
        // pthread_create(&threadID[i], NULL, add, (int*) i);
        add(i);
    }
    peek();
    remove_from_queue();
    peek();
    add(999);
    for(i=0; i<10; i++){
        // pthread_create(&threadID[i], NULL, remove_from_queue);
        remove_from_queue();
        peek();
        printf("\n");
    }
    
    // Close threads
    /*
    for(i=0; i<10; i++) {
      pthread_join(threadID[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    */
    return 0;
}


// Reference:
// For implementing the circular queue: https://www.programiz.com/dsa/circular-queue