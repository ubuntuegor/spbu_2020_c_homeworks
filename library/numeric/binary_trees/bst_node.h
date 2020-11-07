#ifndef SPBU_2020_C_NUMERIC_BST_NODE_H
#define SPBU_2020_C_NUMERIC_BST_NODE_H

typedef struct BinaryTreeNode BinaryTreeNode;

BinaryTreeNode* createBinaryTreeNode(int value);
void destroyBinaryTreeNode(BinaryTreeNode*);

void destroyBinarySubtree(BinaryTreeNode*);

#endif /* SPBU_2020_C_NUMERIC_BST_NODE_H */
