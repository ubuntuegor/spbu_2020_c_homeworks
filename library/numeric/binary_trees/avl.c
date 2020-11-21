#include "avl.h"
#include "node_operations/avl_balancing.h"
#include "node_operations/basic_operations.h"
#include "node_structures/avl_node.h"
#include <stdio.h>
#include <stdlib.h>

struct BalancedTree {
    BalancedTreeNode* root;
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
    updateHeightAndBalanceSubtree(&tree->root, addedOrRemovedValue);
}

bool existsInBalancedTree(BalancedTree* tree, int value)
{
    if (tree == NULL)
        return false;
    return existsInBinarySubtree((BinaryTreeNode*)tree->root, value);
}

bool insertIntoBalancedTree(BalancedTree* tree, int value)
{
    if (tree == NULL)
        return false;

    if (tree->root == NULL) {
        tree->root = createBalancedTreeNode(value);
        updateHeightBalancedTreeNode(tree->root);
        return true;
    }

    BalancedTreeNode* nodeToInsert = createBalancedTreeNode(value);

    bool result = insertIntoBinarySubtree((BinaryTreeNode*)tree->root, (BinaryTreeNode*)nodeToInsert);

    if (!result) {
        destroyBalancedTreeNode(nodeToInsert);
        return false;
    }

    balanceTreeAfterModifying(tree, value);

    return true;
}

bool removeFromBalancedTree(BalancedTree* tree, int value)
{
    if (tree == NULL || tree->root == NULL)
        return false;

    BalancedTreeNode* removedNodePtr = NULL;

    bool result = removeFromBinarySubtree((BinaryTreeNode**)&tree->root, value, (BinaryTreeNode**)&removedNodePtr);
    destroyBalancedTreeNode(removedNodePtr);

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
    printBinarySubtree((BinaryTreeNode*)tree->root);
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
    printAscendingBinarySubtree((BinaryTreeNode*)tree->root);
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
    printDescendingBinarySubtree((BinaryTreeNode*)tree->root);
    printf("\n");
}

bool destroyBalancedTree(BalancedTree* tree)
{
    if (tree == NULL)
        return false;
    destroyBalancedSubtree(tree->root);
    free(tree);
    return true;
}
