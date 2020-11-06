#ifndef SPBU_2020_C_NUMERIC_NODES_AVL_BALANCING_H
#define SPBU_2020_C_NUMERIC_NODES_AVL_BALANCING_H
#include "../avl_node.h"

void updateHeightBalancedTreeNode(BalancedTreeNode*);
int updateHeightAndBalanceSubtree(BalancedTreeNode** nodePtr, int addedOrRemovedValue);

#endif /* SPBU_2020_C_NUMERIC_NODES_AVL_BALANCING_H */
