//
// Created by oeche on 18/10/2025.
//
#include "binary.h"
#include "bsearch.h"

#include <cstddef>

struct _bTree
{
    int element;
    _bTree* left;
    _bTree* right;
};

Tree createEmptyTree(int value)
{
    Tree tree = new _bTree;
    tree->element = value;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

Tree insertNodeBSTree(int value, Tree tree)
{
    if (tree == NULL)
    {
        Tree newTree = new _bTree;
        newTree->element = value;
        newTree->left = NULL;
        newTree->right = NULL;
        return newTree;
    }
    if (value < tree->element)
        tree->left = insertNodeBSTree(value, tree->left);

        // Recurse to the right subtree if value is greater
    else if (value > tree->element)
        tree->right = insertNodeBSTree(value, tree->right);

    // If value == tree->element, do nothing (no duplicates)
    return tree;
}

Tree getRightSideBSTree(Tree tree)
{
    return tree->right;
}

Tree getLeftSideBSTree(Tree tree)
{
    return tree->left;
}

int getMaxfromLeft(Tree tree)
{
    if (tree == NULL || tree->left == NULL)
        return -1; // or handle error

    Tree leftSubtree = tree->left;

    // Go as far right as possible in the left subtree
    while (leftSubtree->right != NULL)
    {
        leftSubtree = leftSubtree->right;
    }

    return leftSubtree->element;
}

int getMaxfromLeft2(Tree tree)
{
    if (tree == NULL)
        return 0; // or handle error

    if (tree->right == NULL)
        return tree->element; // rightmost reached
    return getMaxfromLeft2(tree->right); // go right recursively
}


int getMinfromRight(Tree tree)
{
    if (tree == NULL || tree->right == NULL)
        return 0; // no left subtree

    Tree rightSubtree = tree->right;

    // base case: leftmost node in left subtree
    if (rightSubtree->left == NULL)
        return rightSubtree->element;

    // recursive call: go left in the right subtree
    return getMaxfromLeft(rightSubtree);
}


void deleteNodeBSTree(int value, Tree& tree)
{
    if (tree == NULL)
        return;

    // 1. Recurse into left or right subtree
    if (value < tree->element)
    {
        deleteNodeBSTree(value, tree->left);
    }
    else if (value > tree->element)
    {
        deleteNodeBSTree(value, tree->right);
    }
    else // Found the node to delete
    {
        // 2. Node with only one child or no child
        if (tree->left == NULL)
        {
            Tree temp = tree->right;
            delete tree;
            tree = temp; // ✅ update the reference
            return;
        }
        else if (tree->right == NULL)
        {
            Tree temp = tree->left;
            delete tree;
            tree = temp; // ✅ update the reference
            return;
        }

        // 3. Node with two children
        // Find max in left subtree (in-order predecessor)
        int temp = getMaxfromLeft2(getLeftSideBSTree(tree));

        // Copy its value to current node
        tree->element = temp;

        // Delete the in-order predecessor
        deleteNodeBSTree(temp, tree->left);
    }
}
