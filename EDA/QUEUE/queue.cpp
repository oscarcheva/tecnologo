#include<stdio.h>
#include"queue.h"

struct _nodeQueue
{
    int element;
    _nodeQueue* next;
} typedef * NodeQueue;

struct _queue
{
    int capacity;
    int size;
    _nodeQueue* front;
    _nodeQueue* rear;
};


Queue createNewQueue(int capacity)
{
    Queue queue = new _queue;

    queue->capacity = capacity;
    queue->size = 0;
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void getFirstElement(Queue queue)
{
    if (isQueueEmpty(queue))
        printf("Queue is empty\n");
    else
    {
        printf("The first element is: %d\n", queue->front->element);
    }
}


void enqueue(Queue& queue, int element)
{
    if (isQueueFull(queue))
        printf("Queue is full\n");
    else
    {
        NodeQueue newNode = new _nodeQueue;
        newNode->element = element;
        newNode->next = nullptr;
        if (queue->rear != nullptr)
            queue->rear->next = newNode;
        else
            queue->front = newNode;
        queue->rear = newNode;
        queue->size++;
    }
}

int dequeue(Queue& queue)
{
    if (queue->front == nullptr)
    {
        printf("Queue is empty\n");
        return 0;
    }

    NodeQueue removedNode = queue->front;
    queue->front = queue->front->next;
    int element = removedNode->element;
    delete removedNode;
    queue->size--;
    if (isQueueEmpty(queue))
        queue->rear = nullptr;
    return element;
}

void printQueue(Queue queue)
{
    NodeQueue currentNode = queue->front;
    while (currentNode != nullptr)
    {
        if (currentNode->next != nullptr)
            printf(" %d ->", currentNode->element);
        else
            printf(" %d \n", currentNode->element);

        currentNode = currentNode->next;
    }
}


bool isQueueEmpty(Queue queue)
{
    return queue->size == 0;
}

bool isQueueFull(Queue queue)
{
    return queue->size == queue->capacity;
}

void deleteQueue(Queue queue)
{
    while (!isQueueEmpty(queue))
    {
        dequeue(queue);
    }
    delete queue;
}
