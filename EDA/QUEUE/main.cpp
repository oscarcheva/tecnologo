#include <iostream>
#include "queue.h"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main()
{
    Queue queue = createNewQueue(5);
    dequeue(queue);
    dequeue(queue);
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 4);
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    getFirstElement(queue);
    printf("Dequeued %d\n", dequeue(queue));
    getFirstElement(queue);
    enqueue(queue, 20);
    enqueue(queue, 30);
    printQueue(queue);
    dequeue(queue);
    printQueue(queue);
    return 0;
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}
