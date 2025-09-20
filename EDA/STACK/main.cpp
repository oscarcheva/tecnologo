#include <deque>
#include <iostream>
#include "stack.h"


void printOldestElements(Stack stack, int *limit)
{
    if (isStackEmpty(stack))
        return;

    int element = pop(stack);
    printOldestElements(stack, limit);
    if (*limit > 0)
    {
        printf("%d -> ", element);
        (*limit)--;
    }
    push(stack, element);
}



int main()
{
    setvbuf(stdout, NULL, _IONBF, 0); // disables buffering completely
    Stack stack = createNewStack(5);
    push(stack, 10);
    push(stack, 20);
    printStack(stack);
    printf("Removed %d \n", pop(stack));
    push(stack, 30);
    push(stack, 40);
    push(stack, 50);
    printStack(stack);
    pop(stack);
    printStack(stack);
    int limit = 5;
    printOldestElements(stack,&limit);
    return 0;
}
