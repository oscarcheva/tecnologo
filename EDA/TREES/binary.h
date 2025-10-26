//
// Created by oeche on 18/10/2025.
//

#ifndef BINARY_H
#define BINARY_H

typedef struct _bTree * Tree;

// Constructors / Destructors
Tree createNode(int element);
Tree createCompleteTree();

void deleteTree(Tree tree);
void printInOrder(Tree tree);
void printInOrder(Tree tree, int level);
void printPreOrder(Tree tree);
void printPostOrder(Tree tree);

// Utility
int height(Tree tree);
int heightLeftNodes(Tree tree);
int heightRightNodes(Tree tree);
int countNodes(Tree tree);
bool search(Tree tree, int value);
bool bstSearch(Tree tree, int value);

#endif //BINARY_H
