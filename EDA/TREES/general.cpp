//
// Created by oeche on 18/10/2025.
//

#include "general.h"

#include <cstddef>
#include <cstdio>

typedef struct _genTree
{
    int element;
    GenTree nextBrother;
    GenTree firstChild;
};

GenTree createTree(int element)
{
    GenTree newTree = new _genTree;
    newTree->element = element;
    newTree->firstChild = NULL;
    newTree->nextBrother = NULL;
    return newTree;
}

void addChildNode(GenTree& tree, int parentNode, int childElement)
{
    if (tree != NULL)
    {
        if (tree->element == parentNode)
        {
            if (tree->firstChild == NULL)
                tree->firstChild = createTree(childElement);
            else
                addBrotherNode(tree->firstChild, childElement);
        }
        else
        {
            addChildNode(tree->firstChild, parentNode, childElement);
            addChildNode(tree->nextBrother, parentNode, childElement);
        }
    }
}

void addBrotherNode(GenTree& tree, int element)
{
    if (tree->nextBrother == NULL)
        tree->nextBrother = createTree(element);
    else
        addBrotherNode(tree->nextBrother, element);
}

void printPreOrder(GenTree tree)
{
    if (tree != NULL)
    {
        printf("%d", tree->element);

        if (tree->firstChild != NULL)
        {
            printf(" -> ");
            printPreOrder(tree->firstChild);
        }
        if (tree->nextBrother != NULL)
        {
            printf(" | ");
            printPreOrder(tree->nextBrother);
        }
    }
}

void printPostOrder(GenTree tree)
{
    if (tree != NULL)
    {
        printPostOrder(tree->firstChild);
        printf("%d - ", tree->element);
        printPostOrder(tree->nextBrother);
    }
}

void destroyTree(GenTree tree);
