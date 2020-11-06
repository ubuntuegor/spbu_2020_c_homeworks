#ifndef SPBU_2020_C_NUMERIC_NODES_AVL_STRUCTURE_H
#define SPBU_2020_C_NUMERIC_NODES_AVL_STRUCTURE_H
#include "../avl_node.h"

struct BalancedTreeNode {
    int value;
    BalancedTreeNode* leftChild;
    BalancedTreeNode* rightChild;
    int height;
};

#endif /* SPBU_2020_C_NUMERIC_NODES_AVL_STRUCTURE_H */
