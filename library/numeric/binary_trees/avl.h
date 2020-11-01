#ifndef SPBU_2020_C_NUMERIC_AVL_H
#define SPBU_2020_C_NUMERIC_AVL_H
#include "bst_node.h"
#include <stdbool.h>

typedef struct BalancedTree BalancedTree;

BalancedTree* createBalancedTree();

bool existsInBalancedTree(BalancedTree*, int value);
bool insertIntoBalancedTree(BalancedTree*, int value);
bool removeFromBalancedTree(BalancedTree*, int value);

void printBalancedTree(BalancedTree*);
void printAscendingBalancedTree(BalancedTree*);
void printDescendingBalancedTree(BalancedTree*);

bool destroyBalancedTree(BalancedTree*);

#endif /* SPBU_2020_C_NUMERIC_AVL_H */
