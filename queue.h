#ifndef QUEUE_H
#define QUEUE_H
#include <pthread.h>

// This makes the header file work for both C and C++
#ifdef __cplusplus
extern "C" {
#endif

typedef struct node{
  int val;
  struct node* next;
}node_t;

    
typedef struct my_queue {
  node_t* head;
  node_t* tail;
  pthread_mutex_t headLock;
  pthread_mutex_t tailLock;
} my_queue_t;

// Create a new empty queue
my_queue_t* queue_create();

// Destroy a queue
void queue_destroy(my_queue_t* queue);

// Put an element at the end of a queue
void queue_put(my_queue_t* queue, int element);

// Take an element off the front of a queue
int queue_take(my_queue_t* queue);

// This makes the header file work for both C and C++
#ifdef __cplusplus
}
#endif

#endif
