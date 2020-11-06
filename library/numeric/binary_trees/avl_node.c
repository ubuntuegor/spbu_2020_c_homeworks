#include "avl_node.h"
#include "nodes/avl_structure.h"
#include <stdlib.h>

BinaryTreeNode* createBinaryTreeNode(int value)
{
    BinaryTreeNode* node = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    node->value = value;
    node->height = 0;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}
