#ifndef SPBU_2020_C_NUMERIC_BST_NODE_H
#define SPBU_2020_C_NUMERIC_BST_NODE_H
#include <stdbool.h>

typedef struct BinaryTreeNode BinaryTreeNode;

BinaryTreeNode* createBinaryTreeNode(int value);

int getChildrenCountBinaryTreeNode(BinaryTreeNode*);
int getValueBinaryTreeNode(BinaryTreeNode*);

void updateHeightBinaryTreeNode(BinaryTreeNode*);

int updateHeightAndBalanceBinaryTreeNode(BinaryTreeNode**, int addedOrRemovedValue);

bool existsInBinarySubtree(BinaryTreeNode*, int value);
bool insertIntoBinarySubtree(BinaryTreeNode*, int value);
bool removeFromBinarySubtree(BinaryTreeNode**, int value);

void printBinarySubtree(BinaryTreeNode*);
void printAscendingBinarySubtree(BinaryTreeNode*);
void printDescendingBinarySubtree(BinaryTreeNode*);

void destroyBinarySubtree(BinaryTreeNode*);

#endif /* SPBU_2020_C_NUMERIC_BST_NODE_H */
