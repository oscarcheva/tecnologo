//
// Created by oeche on 18/10/2025.
//
#include "binary.h"
#include <cstddef>
#include <ios>
#include <bits/ios_base.h>

struct _bTree
{
    int element;
    _bTree* left;
    _bTree* right;
};

// Constructors / Destructors
Tree createNode();
Tree createCompleteTree();

void deleteTree(Tree tree);
void printInOrder(Tree tree);
void printPreOrder(Tree tree);
void printPostOrder(Tree tree);
int heightLeftNodes(Tree tree);
int heightRightNodes(Tree tree);


// Utility
int height(Tree tree);
int countNodes(Tree tree);
bool search(Tree tree, int value);

Tree createNode(int element)
{
    Tree tree = new _bTree;
    tree->left = NULL;
    tree->right = NULL;
    tree->element = element;
    return tree;
}

Tree createCompleteTree()
{
    Tree root = createNode(10);
    Tree firstLeftBranch = createNode(8);
    Tree firstRightBranch = createNode(7);
    Tree leftBranchLeftElement = createNode(27);
    Tree rightBranchLeftElement = createNode(79);
    Tree leftBranchRightElement = createNode(67);
    Tree leftBranchRightElementOneMore = createNode(100);
    root->left = firstLeftBranch;
    root->right = firstRightBranch;
    firstLeftBranch->left = leftBranchLeftElement;
    firstLeftBranch->right = leftBranchRightElement;
    firstRightBranch->left = rightBranchLeftElement;
    leftBranchRightElement->right = leftBranchRightElementOneMore;

    return root;
}

void printInOrder(Tree tree)
{
    if (tree != NULL)
    {
        printInOrder(tree->left);
        printf("%d - ", tree->element);
        printInOrder(tree->right);
    }
}

void printPreOrder(Tree tree)
{
    if (tree != NULL)
    {
        printf("%d - ", tree->element);
        printPreOrder(tree->left);
        printPreOrder(tree->right);
    }
}

void printPostOrder(Tree tree)
{
    if (tree != NULL)
    {
        printPostOrder(tree->left);
        printPostOrder(tree->right);
        printf("%d - ", tree->element);
    }
}

void deleteTree(Tree tree)
{
    if (tree != NULL)
    {
        deleteTree(tree->left);
        deleteTree(tree->right);
        delete tree;
    }
}

int height(Tree tree)
{
    if (tree == NULL)
        return 0;

    int leftHeight = height(tree->left);
    int rightHeight = height(tree->right);

    // Add +1 only if there's at least one child (i.e., there’s an edge)
    if (tree->left != NULL || tree->right != NULL)
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    return 0; // leaf has no edges
}

int heightLeftNodes(Tree tree)
{
    if (tree == NULL)
        return 0;

    int leftHeight = height(tree->left);
    height(tree->right);

    // Add +1 only if there's at least one child (i.e., there’s an edge)
    if (tree->left != NULL || tree->right != NULL)
        return 1 + leftHeight;
    return 0; // leaf has no edges
}

int heightRightNodes(Tree tree)
{
    if (tree == NULL)
        return 0;

    height(tree->left);
    int rightHeight = height(tree->right);

    // Add +1 only if there's at least one child (i.e., there’s an edge)
    if (tree->left != NULL || tree->right != NULL)
        return 1 + rightHeight;
    return 0; // leaf has no edges
}

int countNodes(Tree tree)
{
    if (tree == NULL)
        return 0;
    return 1 + countNodes(tree->left) + countNodes(tree->right);
}

bool search(Tree tree, int value)
{
    if (tree == NULL)
        return false;
    if (tree->element == value)
        return true;
    return search(tree->left, value) || search(tree->right, value);
}

bool bstSearch(Tree tree, int value)
{
    if (tree == NULL)
        return false;
    if (tree->element == value)
        return true;
    if (value<tree->element)
        return bstSearch(tree->left, value);
    return bstSearch(tree->right, value);
}
