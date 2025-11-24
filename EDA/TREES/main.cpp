#include <iostream>
#include "binary.h"
#include "bsearch.h"
#include "general.h"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
void testBTrees()
{
    Tree tree = createCompleteTree();
    printf("InOrder Printing");
    printf("\n");
    printf("----------------------------------");
    printf("\n");
    printInOrder(tree);
    printf("\n");

    printf("----------------------------------");
    printf("\n");
    printf("PreOrder Printing");
    printf("\n");
    printf("----------------------------------");
    printf("\n");
    printPreOrder(tree);
    printf("\n");
    printf("----------------------------------");
    printf("\n");
    printf("PostOrder Printing");
    printf("\n");
    printf("----------------------------------");
    printf("\n");
    printPostOrder(tree);
    printf("\n");
    printf("----------------------------------");
    printf("\n");
    printf("Tree height: %d \n", height(tree));
    printf("Tree Left Nodes height: %d \n", heightLeftNodes(tree));
    printf("Tree Right Nodes height: %d \n", heightRightNodes(tree));
    printf("Total nodes: %d \n", countNodes(tree));
    printf("Element 32 exists?: %d \n", search(tree, 32));
    printf("Element 31 exists?: %d \n", search(tree, 67));

    deleteTree(tree);

    Tree tree2 = createEmptyTree(15);

    insertNodeBSTree(5, tree2);
    insertNodeBSTree(10, tree2);
    insertNodeBSTree(4, tree2);
    insertNodeBSTree(9, tree2);
    insertNodeBSTree(22, tree2);
    insertNodeBSTree(55, tree2);
    insertNodeBSTree(32, tree2);
    insertNodeBSTree(6, tree2);
    insertNodeBSTree(3, tree2);
    insertNodeBSTree(16, tree2);
    insertNodeBSTree(17, tree2);

    printf("InOrder Printing");
    printf("\n");
    printf("----------------------------------");
    printf("\n");
    printInOrder(tree2);
    printf("\n");

    printf("----------------------------------");
    printf("\n");

    // deleteNodeBSTree(15,tree2);

    printf("InOrder Printing");
    printf("\n");
    printf("----------------------------------");
    printf("\n");
    printInOrder(tree2);
    printf("\n");

    printf("----------------------------------");
    printf("\n");

    printf("%d \n", getMaxfromLeft2(getLeftSideBSTree(tree2)));

    deleteNodeBSTree(16, tree2);

    printf("InOrder Printing");
    printf("\n");
    printf("----------------------------------");
    printf("\n");
    printInOrder(tree2);
    printf("\n");

    printf("----------------------------------");
    printf("\n");

    printf("%d \n", getMaxfromLeft2(getLeftSideBSTree(tree2)));
}

void testGenTrees()
{

    GenTree rootTree = createTree(100);
    addChildNode(rootTree, 100, 80);
    addChildNode(rootTree, 100, 60);
    addChildNode(rootTree, 100, 40);
    addChildNode(rootTree, 100, 20);
    addChildNode(rootTree, 100, 10);
    addChildNode(rootTree, 80, 81);
    addChildNode(rootTree, 80, 82);
    addChildNode(rootTree, 60, 61);
    addChildNode(rootTree, 20, 21);
    addChildNode(rootTree, 20, 22);
    addChildNode(rootTree, 20, 23);

    printPreOrder(rootTree);

    printf("\n");

    printPostOrder(rootTree);
}

int main()
{
    testBTrees();
    // testGenTrees();
    return 0;
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}
