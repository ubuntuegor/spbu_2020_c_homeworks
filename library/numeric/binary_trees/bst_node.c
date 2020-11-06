#include "bst_node.h"
#include "nodes/bst_structure.h"
#include <stdlib.h>

BinaryTreeNode* createBinaryTreeNode(int value)
{
    BinaryTreeNode* node = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    node->value = value;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

void destroyBinaryTreeNode(BinaryTreeNode* node)
{
    if (node == NULL)
        return;
    free(node);
}

void destroyBinarySubtree(BinaryTreeNode* node)
{
    if (node == NULL)
        return;
    destroyBinarySubtree(node->leftChild);
    destroyBinarySubtree(node->rightChild);
    free(node);
}
