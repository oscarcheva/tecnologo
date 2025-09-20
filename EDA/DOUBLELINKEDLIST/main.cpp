#include <iostream>
#include "doublelist.h"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main()
{
    DLlist list = createNewList();
    insertFront(list, 1);
    insertFront(list, 2);
    insertFront(list, 3);
    insertFront(list, 4);
    insertFront(list, 5);
    insertBack(list, 6);
    insertBack(list, 7);
    insertBack(list, 8);
    insertBack(list, 9);
    insertBack(list, 10);
    printListElements(list);
    insertAtIndex(list,11,2);
    printListElements(list);
    removeFront(list);
    removeBack(list);
    printListElements(list);
    removeAtIndex(list,2);
    printListElements(list);

    return 0;
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}
