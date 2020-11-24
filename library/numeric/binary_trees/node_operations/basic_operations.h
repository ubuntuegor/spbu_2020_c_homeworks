#ifndef SPBU_2020_C_NUMERIC_NODES_BST_OPERATIONS_H
#define SPBU_2020_C_NUMERIC_NODES_BST_OPERATIONS_H
#include "../node_structures/bst_node.h"
#include <stdbool.h>

int getChildrenCountBinaryTreeNode(BinaryTreeNode*);
int getValueBinaryTreeNode(BinaryTreeNode*);

bool existsInBinarySubtree(BinaryTreeNode*, int value);
bool insertIntoBinarySubtree(BinaryTreeNode*, BinaryTreeNode* nodeToInsert);
bool removeFromBinarySubtree(BinaryTreeNode** nodePtr, int value, BinaryTreeNode** removedNodePtr);

void printBinarySubtree(BinaryTreeNode*);
void printAscendingBinarySubtree(BinaryTreeNode*);
void printDescendingBinarySubtree(BinaryTreeNode*);

#endif /* SPBU_2020_C_NUMERIC_NODES_BST_OPERATIONS_H */
