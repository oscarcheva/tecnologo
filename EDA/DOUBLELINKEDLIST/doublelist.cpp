//
// Created by oeche on 16/09/2025.
//

#include <stdio.h>
#include "doublelist.h"

#include <exception>
#include <ranges>

struct _nodeList
{
    int element;
    _nodeList* next;
    _nodeList* previous;
} typedef * NodeList;

struct _DLlist
{
    int size;
    _nodeList* head;
    _nodeList* tail;
};

DLlist createNewList()
{
    DLlist list = new _DLlist;
    list->size = 0;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

void insertFront(DLlist list, int element)
{
    NodeList node = new _nodeList;
    node->element = element;
    node->previous = nullptr;
    node->next = list->head;
    if (list->head != nullptr)
        list->head->previous = node;
    list->head = node;
    if (list->tail == nullptr)
        list->tail = node;
    list->size++;
}

void insertBack(DLlist list, int element)
{
    NodeList node = new _nodeList;
    node->element = element;
    node->next = nullptr;
    node->previous = list->tail;
    if (list->tail != nullptr)
        list->tail->next = node;
    list->tail = node;
    if (list->head == nullptr)
        list->head = node;
    list->size++;
}

void insertAtIndex(DLlist list, int element, int index)
{
    NodeList node = new _nodeList;
    node->element = element;
    if (isListEmpty(list))
    {
        printf("List is empty, element will be inserted at the front");
        insertFront(list, element);
    }
    else
    {
        NodeList current = getNodeAtIndex(list, index);
        node->previous = current->previous;
        node->next = current;
        if (current->previous != nullptr)
            current->previous->next = node;
        current->previous = node;
    }
    list->size++;
}


int removeFront(DLlist list)
{
    if (isListEmpty(list))
    {
        printf("List is empty, nothing to remove");
        return -1;
    }
    NodeList toBeDeleted = getFirstNode(list);
    int element = toBeDeleted->element;
    list->head = toBeDeleted->next;
    if (list->head != nullptr)
        list->head->previous = nullptr;
    delete toBeDeleted;
    list->size--;
    if (list->head == nullptr)
        list->tail = nullptr;
    return element;
}

int removeBack(DLlist list)
{
    if (isListEmpty(list))
    {
        printf("List is empty, nothing to remove");
        return -1;
    }
    NodeList toBeDeleted = getLastNode(list);
    int element = toBeDeleted->element;
    list->tail = toBeDeleted->previous;
    if (list->tail != nullptr)
        list->tail->next = nullptr;
    delete toBeDeleted;
    list->size--;
    if (list->tail == nullptr)
        list->head = nullptr;
    return element;
}

int removeAtIndex(DLlist list, int index)
{
    if (isListEmpty(list))
    {
        printf("List is empty, nothing to remove");
        return -1;
    }
    if (index > list->size - 1 || index < 0)
    {
        printf("Out of bounds");
        return -1;
    }
    if (index == 0)
        return removeFront(list);
    if (index == list->size - 1)
        return removeBack(list);

    NodeList toBeDeleted = getNodeAtIndex(list, index);
    int element = toBeDeleted->element;
    toBeDeleted->next->previous = toBeDeleted->previous;
    toBeDeleted->previous->next = toBeDeleted->next;
    delete toBeDeleted;
    list->size--;
    return element;
}

NodeList getFirstNode(DLlist list)
{
    return list->head;
}

NodeList getLastNode(DLlist list)
{
    return list->tail;
}

NodeList getNodeAtIndex(DLlist list, int index)
{
    if (index == 0)
        return getFirstNode(list);
    if (index == list->size - 1)
        return getLastNode(list);
    if (index > list->size - 1)
            return nullptr;
        NodeList current = list->head;
        if (index < list->size / 2)
            for (int x = 0; x < index; x++)
                current = current->next;
        else
        {
            current = list->tail;
            for (int x = list->size - 1; x > index; x--)
                current = current->previous;
        }

        return current;
}

void deleteList(DLlist list)
{
    while (!isListEmpty(list))
    {
        removeAtIndex(list, 0);
    }
    delete list;
}

void printListElements(DLlist list)
{
    if (isListEmpty(list))
    {
        printf("List is empty, nothing to print");
        return;
    }
    NodeList current = list->head;
    while (current->next != nullptr)
    {
        if (current != list->tail)
            printf("%d <-> ", current->element);
        current = current->next;
    }
    printf("%d\n", current->element);

}

bool isListEmpty(DLlist list)
{
    return list->head == nullptr;
}