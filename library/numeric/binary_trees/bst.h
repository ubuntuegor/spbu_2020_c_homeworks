#ifndef SPBU_2020_C_NUMERIC_BST_H
#define SPBU_2020_C_NUMERIC_BST_H
#include "bst_node.h"
#include <stdbool.h>

typedef struct BinaryTree BinaryTree;

BinaryTree* createBinaryTree();

bool existsBinaryTree(BinaryTree*, int value);
bool insertBinaryTree(BinaryTree*, int value);
bool removeBinaryTree(BinaryTree*, int value);

void printBinaryTree(BinaryTree*);
void printAscendingBinaryTree(BinaryTree*);
void printDescendingBinaryTree(BinaryTree*);

bool destroyBinaryTree(BinaryTree*);

#endif /* SPBU_2020_C_NUMERIC_BST_H */
