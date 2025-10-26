//
// Created by oeche on 18/10/2025.
//

#ifndef BSEARCH_H
#define BSEARCH_H

#include "binary.h" // include your BTree typedef and existing functions

// Constructors / Destructors
Tree createEmptyTree(int value);
Tree insertNodeBSTree(int value, Tree tree);
void deleteNodeBSTree(int value, Tree &tree);
Tree getRightSideBSTree(Tree tree);
Tree getLeftSideBSTree(Tree tree);
int getMaxfromLeft(Tree tree);
int getMaxfromLeft2(Tree tree);
int getMinfromRight(Tree tree);

#endif //BSEARCH_H
