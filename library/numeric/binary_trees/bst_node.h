#ifndef SPBU_2020_C_NUMERIC_BST_NODE_H
#define SPBU_2020_C_NUMERIC_BST_NODE_H
#include <stdbool.h>

typedef struct BinaryTreeNode BinaryTreeNode;

BinaryTreeNode* createBinaryTreeNode(int value);

int getChildrenCountBinaryTreeNode(BinaryTreeNode*);
int getValueBinaryTreeNode(BinaryTreeNode*);

bool existsBinaryTreeFromNode(BinaryTreeNode*, int value);
bool insertBinaryTreeFromNode(BinaryTreeNode*, int value);
bool removeBinaryTreeFromNode(BinaryTreeNode**, int value);

void printBinaryTreeFromNode(BinaryTreeNode*);
void printAscendingBinaryTreeFromNode(BinaryTreeNode*);
void printDescendingBinaryTreeFromNode(BinaryTreeNode*);

void destroyBinaryTreeFromNode(BinaryTreeNode*);

#endif /* SPBU_2020_C_NUMERIC_BST_NODE_H */
