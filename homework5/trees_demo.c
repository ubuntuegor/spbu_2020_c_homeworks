#include "../library/numeric/binary_trees/avl.h"
#include "../library/numeric/binary_trees/bst.h"
#include "../library/numeric/io.h"
#include <stdio.h>

void askForValueAndInsert(BinaryTree* tree1, BalancedTree* tree2)
{
    int value = 0;
    promptInt("Integer value to insert: ", &value);
    bool result = insertIntoBinaryTree(tree1, value) && insertIntoBalancedTree(tree2, value);
    if (result)
        printf("Value inserted successfully!\n\n");
    else
        printf("Failed to insert value. Most likely it's already in the tree.\n\n");
}

void askForValueAndRemove(BinaryTree* tree1, BalancedTree* tree2)
{
    int value = 0;
    promptInt("Integer value to remove: ", &value);
    bool result = removeFromBinaryTree(tree1, value) && removeFromBalancedTree(tree2, value);
    if (result)
        printf("Value removed successfully!\n\n");
    else
        printf("Failed to removed value. Most likely it was not in the tree.\n\n");
}

void askForValueAndCheckIfExists(BinaryTree* tree1, BalancedTree* tree2)
{
    int value = 0;
    promptInt("Integer value to find: ", &value);
    bool result = existsInBinaryTree(tree1, value) && existsInBalancedTree(tree2, value);
    if (result)
        printf("%d is in the tree.\n\n", value);
    else
        printf("%d is not in the tree.\n\n", value);
}

void printInRequestedFormat(BinaryTree* tree1, BalancedTree* tree2)
{
    printf("Select format:\n"
           "1. Ascending.\n"
           "2. Descending.\n"
           "3. As tree.\n"
           "0. Go back.\n"
           "\n");
    int format = 0;
    promptInt("Enter format number: ", &format);

    if (format == 1) {
        printf("Binary tree: ");
        printAscendingBinaryTree(tree1);
        printf("Balanced tree: ");
        printAscendingBalancedTree(tree2);
    } else if (format == 2) {
        printf("Binary tree: ");
        printDescendingBinaryTree(tree1);
        printf("Balanced tree: ");
        printDescendingBalancedTree(tree2);
    } else if (format == 3) {
        printf("Binary tree: ");
        printBinaryTree(tree1);
        printf("Balanced tree: ");
        printBalancedTree(tree2);
    }
    printf("\n");
}

int selectAndCommitAction(BinaryTree* tree1, BalancedTree* tree2)
{
    printf("Select action:\n"
           "1: Insert value.\n"
           "2: Remove value.\n"
           "3: Check if value exists.\n"
           "4: Print the tree.\n"
           "0: Exit.\n"
           "\n");
    int selection = 0;
    promptInt("Enter action number: ", &selection);

    if (selection == 1) {
        askForValueAndInsert(tree1, tree2);
    } else if (selection == 2) {
        askForValueAndRemove(tree1, tree2);
    } else if (selection == 3) {
        askForValueAndCheckIfExists(tree1, tree2);
    } else if (selection == 4) {
        printInRequestedFormat(tree1, tree2);
    } else if (selection != 0) {
        printf("No such action.\n\n");
    }

    return selection;
}

int main()
{
    BinaryTree* tree1 = createBinaryTree();
    BalancedTree* tree2 = createBalancedTree();
    printf("Two Trees Demo\n\n");

    int selection = 1;
    while (selection != 0) {
        selection = selectAndCommitAction(tree1, tree2);
    }

    destroyBinaryTree(tree1);
    destroyBalancedTree(tree2);
    return 0;
}
