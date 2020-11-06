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
