#ifndef SPBU_2020_C_NUMERIC_NODES_BST_OPERATIONS_H
#define SPBU_2020_C_NUMERIC_NODES_BST_OPERATIONS_H
#include "../bst_node.h"
#include <stdbool.h>

int getChildrenCountBinaryTreeNode(BinaryTreeNode*);
int getValueBinaryTreeNode(BinaryTreeNode*);

bool existsInBinarySubtree(BinaryTreeNode*, int value);
bool insertIntoBinarySubtree(BinaryTreeNode*, int value);
bool removeFromBinarySubtree(BinaryTreeNode**, int value);

void printBinarySubtree(BinaryTreeNode*);
void printAscendingBinarySubtree(BinaryTreeNode*);
void printDescendingBinarySubtree(BinaryTreeNode*);

void destroyBinarySubtree(BinaryTreeNode*);

#endif /* SPBU_2020_C_NUMERIC_NODES_BST_OPERATIONS_H */
