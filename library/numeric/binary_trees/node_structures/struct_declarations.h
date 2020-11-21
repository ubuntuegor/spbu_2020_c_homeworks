#ifndef SPBU_2020_C_NUMERIC_NODE_STRUCT_DECLARATIONS_H
#define SPBU_2020_C_NUMERIC_NODE_STRUCT_DECLARATIONS_H

struct BinaryTreeNode {
    int value;
    struct BinaryTreeNode* leftChild;
    struct BinaryTreeNode* rightChild;
};

struct BalancedTreeNode {
    int value;
    struct BalancedTreeNode* leftChild;
    struct BalancedTreeNode* rightChild;
    int height;
};

#endif /* SPBU_2020_C_NUMERIC_NODE_STRUCT_DECLARATIONS_H */