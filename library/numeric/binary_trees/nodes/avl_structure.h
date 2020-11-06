#ifndef SPBU_2020_C_NUMERIC_NODES_AVL_STRUCTURE_H
#define SPBU_2020_C_NUMERIC_NODES_AVL_STRUCTURE_H
#include "../avl_node.h"

struct BinaryTreeNode {
    int value;
    int height;
    BinaryTreeNode* leftChild;
    BinaryTreeNode* rightChild;
};

#endif /* SPBU_2020_C_NUMERIC_NODES_AVL_STRUCTURE_H */
