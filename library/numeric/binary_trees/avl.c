#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

struct BalancedTree {
    BinaryTreeNode* root;
};

BalancedTree* createBalancedTree()
{
    BalancedTree* tree = (BalancedTree*)malloc(sizeof(BalancedTree));
    tree->root = NULL;
    return tree;
};

void balanceTreeAfterModifying(BalancedTree* tree, int addedOrRemovedValue)
{
    if (tree == NULL)
        return;
    updateHeightAndBalanceBinaryTreeNode(&(tree->root), addedOrRemovedValue);
}

bool existsInBalancedTree(BalancedTree* tree, int value)
{
    if (tree == NULL)
        return false;
    return existsInBinaryTreeFromNode(tree->root, value);
}

bool insertIntoBalancedTree(BalancedTree* tree, int value)
{
    if (tree == NULL)
        return false;

    if (tree->root == NULL) {
        tree->root = createBinaryTreeNode(value);
        updateHeightBinaryTreeNode(tree->root);
        return true;
    }

    bool result = insertIntoBinaryTreeFromNode(tree->root, value);

    if (!result)
        return false;

    balanceTreeAfterModifying(tree, value);

    return true;
}

bool removeFromBalancedTree(BalancedTree* tree, int value)
{
    if (tree == NULL || tree->root == NULL)
        return false;

    bool result = removeFromBinaryTreeFromNode(&(tree->root), value);

    if (!result)
        return false;

    balanceTreeAfterModifying(tree, value);

    return true;
}

void printBalancedTree(BalancedTree* tree)
{
    if (tree == NULL) {
        printf("()");
        return;
    }
    printBinaryTreeFromNode(tree->root);
    printf("\n");
}

void printAscendingBalancedTree(BalancedTree* tree)
{
    if (tree == NULL) {
        printf("Not a tree.\n");
        return;
    }
    if (tree->root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    printAscendingBinaryTreeFromNode(tree->root);
    printf("\n");
}
void printDescendingBalancedTree(BalancedTree* tree)
{
    if (tree == NULL) {
        printf("Not a tree.\n");
        return;
    }
    if (tree->root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    printDescendingBinaryTreeFromNode(tree->root);
    printf("\n");
}

bool destroyBalancedTree(BalancedTree* tree)
{
    if (tree == NULL)
        return false;
    destroyBinaryTreeFromNode(tree->root);
    free(tree);
    return true;
}
