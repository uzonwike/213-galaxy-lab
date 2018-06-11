#include "queue.h"
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>

// Create a new empty queue
my_queue_t* queue_create() {
  node_t* tmp = (node_t*) malloc(sizeof(node_t));
  my_queue_t* newQueue = (my_queue_t*) malloc(sizeof(my_queue_t));
  tmp->next = NULL;
  newQueue->head = newQueue->tail = tmp;
  pthread_mutex_init(&newQueue->headLock, NULL);
  pthread_mutex_init(&newQueue->tailLock, NULL);
  return newQueue;
}

// Destroy a queue
void queue_destroy(my_queue_t* queue) {
  pthread_mutex_lock(&queue->tailLock);
  pthread_mutex_lock(&queue->headLock);
  
  if(queue->head == NULL){return;}
  node_t* prev = queue->head;
  node_t* curr = queue->head;
  while(curr != NULL){
    prev = curr;
    curr = curr->next;
    free(prev);
  }
  free(prev);
  pthread_mutex_unlock(&queue->tailLock);
  pthread_mutex_unlock(&queue->headLock);
}

// Put an element at the end of a queue
void queue_put(my_queue_t* queue, int element) {
  node_t* newNode = (node_t*) malloc(sizeof(node_t));
  assert(newNode != NULL);
  newNode->val = element;
  newNode->next = NULL;
  
  pthread_mutex_lock(&queue->tailLock);
  
    queue->tail->next = newNode;
    queue->tail = newNode;

  pthread_mutex_unlock(&queue->tailLock);

}

// Take an element off the front of a queue
int queue_take(my_queue_t* queue) {

  pthread_mutex_lock(&queue->headLock);

  node_t* tmp = queue->head;
  node_t *newHead = tmp->next;

  if(newHead == NULL) {
    pthread_mutex_unlock(&queue->headLock);
    return -1;
  }
  int ret = newHead->val;
  queue->head = newHead;

  pthread_mutex_unlock(&queue->headLock);

  free(tmp);

  return ret;
}
