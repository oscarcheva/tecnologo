//
// Created by oeche on 16/09/2025.
//

#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

typedef struct _DLlist* DLlist;

typedef struct _nodeList * NodeList;

// **** Constructors

// PreCond: none
// PostCond: returns a new empty double linked list with a fixed capacity

DLlist createNewList();

// PreCond: List must not be full
// PostCond: inserts a new element at the front of the list

void insertFront(DLlist list, int element);

// PreCond: List must not be full
// PostCond: inserts a new element at the front of the list
void insertBack(DLlist list, int element);

// PreCond: List must not be full
// PostCond: inserts a new element at specific position
void insertAtIndex(DLlist list, int element, int index);

// PreCond: List must not be empty
// PostCond: Removes an element at the front of the list and returns it
int removeFront(DLlist list);

// PreCond: List must not be empty
// PostCond: Removes an element at the front of the list and returns it
int removeBack(DLlist list);

// PreCond: List must not be empty
// PostCond: Removes an element at the front of the list and returns it
int removeAtIndex(DLlist list, int index);

// **** Accessors / Selectors

// PreCond: List must not be empty
// PostCond: Returns the first node of the list
NodeList getFirstNode(DLlist list);

// PreCond: List must not be empty
// PostCond: Returns the last node of the list
NodeList getLastNode(DLlist list);

// PreCond: List must not be empty
// PostCond: Returns a specific node of the list
NodeList getNodeAtIndex(DLlist list, int index);

void printListElements(DLlist list);

// **** Destructors

// PreCond: A List must have been created
// PostCond: Removes every element in the list and then deletes it
void deleteList(DLlist list);


// **** Predicates

// PreCond: A List must have been created
// PostCond: Returns true if the List has no elements
bool isListEmpty(DLlist list);


#endif
