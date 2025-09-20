//
// Created by oeche on 15/09/2025.
//

#include "stack.h"
#include <stdio.h>


struct nodeStack
{
    int element;
    nodeStack* next;
}typedef * StackNode;

struct _stack
{
    int capacity;
    int size;
    nodeStack* top;
};

Stack createNewStack(int capacity)
{
    Stack stack = new _stack;
    stack->capacity = capacity;
    stack->size = 0;
    stack->top = nullptr;
    return stack;
}

void push(Stack& stack, int element)
{
    if (isStackFull(stack))
        printf("Stack is full\n");
    else
    {
        StackNode newNode = new nodeStack;
        newNode->element = element;
        newNode->next = stack->top;
        stack->top = newNode;
        stack->size++;
    }
}

int pop(Stack& stack)
{
    if (isStackEmpty(stack))
    {
        printf("Stack is empty\n");
        return 0;
    }
    StackNode deletedNode = stack->top;
    stack->top = deletedNode->next;
    int element = deletedNode->element;
    stack->size--;
    delete deletedNode;
    return element;
}

void printStack(Stack stack)
{
    if (isStackEmpty(stack))
        printf("Stack is empty\n");
    else
    {
        StackNode currentNode = stack->top;
        while (currentNode != nullptr)
        {
            printf("%d \n", currentNode->element);
            if (currentNode->next != nullptr)
                printf("--\n");
            currentNode = currentNode->next;
        }
    }
    printf("------------------------------------------------------\n");

}


bool isStackEmpty(Stack stack)
{
    return stack->size == 0;
}

// PreCond: A stack must have been created
// PostCond: Returns true if the stack has met its capacity
bool isStackFull(Stack stack)
{
    return stack->size == stack->capacity;
}
