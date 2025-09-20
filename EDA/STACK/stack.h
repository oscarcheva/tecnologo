//
// Created by oeche on 15/09/2025.
//

#ifndef stack_h
#define stack_h

typedef struct _stack * Stack;

// **** Constructors

// PreCond: none
// PostCond: returns a new empty stack with a fixed capacity

Stack createNewStack(int capacity);

// **** Accessors / Selectors

// PreCond: stack must not be full
// PostCond: inserts a new element at the top of the stack
void push(Stack &stack, int element);

// PreCond: stack must not be empty
// PostCond: returns the element at the top of the stack and removes it
int pop (Stack &stack);

void printStack(Stack stack);

// **** Destructors
// PreCond: A stack must have been created
// PostCond: Removes every element in the stack and then deletes it
void deleteStack(Stack stack);

// **** Predicates

// PreCond: A stack must have been created
// PostCond: Returns true if the stack has no elements
bool isStackEmpty(Stack stack);

// PreCond: A stack must have been created
// PostCond: Returns true if the stack has met its capacity
bool isStackFull(Stack stack);


#endif