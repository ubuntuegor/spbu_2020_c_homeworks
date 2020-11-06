#include "bst.h"
#include "bst_node.h"
#include <stdio.h>
#include <stdlib.h>

struct BinaryTree {
    BinaryTreeNode* root;
};

BinaryTree* createBinaryTree()
{
    BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));
    tree->root = NULL;
    return tree;
}

bool existsInBinaryTree(BinaryTree* tree, int value)
{
    if (tree == NULL)
        return false;
    return existsInBinarySubtree(tree->root, value);
}

bool insertIntoBinaryTree(BinaryTree* tree, int value)
{
    if (tree == NULL)
        return false;

    if (tree->root == NULL) {
        tree->root = createBinaryTreeNode(value);
        return true;
    }

    return insertIntoBinarySubtree(tree->root, value);
}

bool removeFromBinaryTree(BinaryTree* tree, int value)
{
    if (tree == NULL || tree->root == NULL)
        return false;

    return removeFromBinarySubtree(&(tree->root), value);
}

void printBinaryTree(BinaryTree* tree)
{
    if (tree == NULL) {
        printf("()");
        return;
    }
    printBinarySubtree(tree->root);
    printf("\n");
}

void printAscendingBinaryTree(BinaryTree* tree)
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
void printDescendingBinaryTree(BinaryTree* tree)
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

bool destroyBinaryTree(BinaryTree* tree)
{
    if (tree == NULL)
        return false;
    destroyBinarySubtree(tree->root);
    free(tree);
    return true;
}
