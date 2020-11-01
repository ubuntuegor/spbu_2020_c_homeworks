#include "../library/numeric/binary_trees/avl.h"
#include "../library/numeric/io.h"
#include <stdio.h>

void askForValueAndInsert(BalancedTree* tree)
{
    int value = 0;
    promptInt("Integer value to insert: ", &value);
    bool result = insertBalancedTree(tree, value);
    if (result)
        printf("Value inserted succesfully!\n\n");
    else
        printf("Failed to insert value. Most likely it's already in the tree.\n\n");
}

void askForValueAndRemove(BalancedTree* tree)
{
    int value = 0;
    promptInt("Integer value to remove: ", &value);
    bool result = removeBalancedTree(tree, value);
    if (result)
        printf("Value removed succesfully!\n\n");
    else
        printf("Failed to removed value. Most likely it was not in the tree.\n\n");
}

void askForValueAndCheckIfExists(BalancedTree* tree)
{
    int value = 0;
    promptInt("Integer value to find: ", &value);
    bool result = existsBalancedTree(tree, value);
    if (result)
        printf("%d is in the tree.\n\n", value);
    else
        printf("%d is not in the tree.\n\n", value);
}

void printInRequestedFormat(BalancedTree* tree)
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
        printAscendingBalancedTree(tree);
    } else if (format == 2) {
        printDescendingBalancedTree(tree);
    } else if (format == 3) {
        printBalancedTree(tree);
    }
    printf("\n");
}

int selectAndCommitAction(BalancedTree* tree)
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
        askForValueAndInsert(tree);
    } else if (selection == 2) {
        askForValueAndRemove(tree);
    } else if (selection == 3) {
        askForValueAndCheckIfExists(tree);
    } else if (selection == 4) {
        printInRequestedFormat(tree);
    } else if (selection != 0) {
        printf("No such action.\n\n");
    }

    return selection;
}

int main()
{
    BalancedTree* tree = createBalancedTree();
    printf("Binary Search Tree\n\n");

    int selection = 1;
    while (selection != 0) {
        selection = selectAndCommitAction(tree);
    }

    destroyBalancedTree(tree);
    return 0;
}
