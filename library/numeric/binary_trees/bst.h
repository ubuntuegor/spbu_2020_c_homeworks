#ifndef SPBU_2020_C_NUMERIC_BST_H
#define SPBU_2020_C_NUMERIC_BST_H
#include <stdbool.h>

typedef struct BinaryTree BinaryTree;

BinaryTree* createBinaryTree();

bool existsInBinaryTree(BinaryTree*, int value);
bool insertIntoBinaryTree(BinaryTree*, int value);
bool removeFromBinaryTree(BinaryTree*, int value);

void printBinaryTree(BinaryTree*);
void printAscendingBinaryTree(BinaryTree*);
void printDescendingBinaryTree(BinaryTree*);

bool destroyBinaryTree(BinaryTree*);

#endif /* SPBU_2020_C_NUMERIC_BST_H */
