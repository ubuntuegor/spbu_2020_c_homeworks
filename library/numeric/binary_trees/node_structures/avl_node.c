#include "avl_node.h"
#include "struct_declarations.h"
#include <stdlib.h>

BalancedTreeNode* createBalancedTreeNode(int value)
{
    BalancedTreeNode* node = (BalancedTreeNode*)malloc(sizeof(BalancedTreeNode));
    node->value = value;
    node->height = 0;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

void destroyBalancedTreeNode(BalancedTreeNode* node)
{
    if (node == NULL)
        return;
    free(node);
}

void destroyBalancedSubtree(BalancedTreeNode* node)
{
    if (node == NULL)
        return;
    destroyBalancedSubtree(node->leftChild);
    destroyBalancedSubtree(node->rightChild);
    free(node);
}
