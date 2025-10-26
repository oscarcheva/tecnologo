//
// Created by oeche on 18/10/2025.
//

#ifndef GENERAL_H
#define GENERAL_H

typedef struct _genTree * GenTree;

GenTree createTree(int element);
void addChildNode(GenTree &tree, int parentNode, int childElement);
void addBrotherNode(GenTree &tree, int element);

void printPreOrder(GenTree tree);
void printPostOrder(GenTree tree);

void destroyTree(GenTree tree);

#endif //GENERAL_H
