#include "avl.h"
#include "avl_node.h"
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
    updateHeightAndBalanceBinarySubtree(&(tree->root), addedOrRemovedValue);
}

bool existsInBalancedTree(BalancedTree* tree, int value)
{
    if (tree == NULL)
        return false;
    return existsInBinarySubtree(tree->root, value);
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

    bool result = insertIntoBinarySubtree(tree->root, value);

    if (!result)
        return false;

    balanceTreeAfterModifying(tree, value);

    return true;
}

bool removeFromBalancedTree(BalancedTree* tree, int value)
{
    if (tree == NULL || tree->root == NULL)
        return false;

    bool result = removeFromBinarySubtree(&(tree->root), value);

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
    printBinarySubtree(tree->root);
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
    printAscendingBinarySubtree(tree->root);
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
    printDescendingBinarySubtree(tree->root);
    printf("\n");
}

bool destroyBalancedTree(BalancedTree* tree)
{
    if (tree == NULL)
        return false;
    destroyBinarySubtree(tree->root);
    free(tree);
    return true;
}
