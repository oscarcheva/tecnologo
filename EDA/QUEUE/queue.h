#ifndef queue_h
#define queue_h
#include <stdbool.h>

typedef struct _queue * Queue;

// **** Constructors

// PreCond: none
// PostCond: returns a new empty queue with a fixed capacity

Queue createNewQueue(int capacity);

// PreCond: queue must not be full
// PostCond: inserts a new element at the back of the queue

// **** Accessors / Selectors

// PreCond: queue must not be empty
// PostCond: returns the element at the front of the queue and removes it
int dequeue(Queue &queue);

void enqueue (Queue &queue, int element);

void getFirstElement(Queue queue);

void printQueue(Queue queue);

// **** Destructors
// PreCond: A queue must have been created
// PostCond: Removes every element in the queue and then deletes it
void deleteQueue(Queue queue);

// **** Predicates

// PreCond: A queue must have been created
// PostCond: Returns true if the queue has no elements
bool isQueueEmpty(Queue queue);

// PreCond: A queue must have been created
// PostCond: Returns true if the queue has met its capacity
bool isQueueFull(Queue queue);


#endif
