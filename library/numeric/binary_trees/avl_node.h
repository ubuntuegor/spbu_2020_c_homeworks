#ifndef SPBU_2020_C_NUMERIC_AVL_NODE_H
#define SPBU_2020_C_NUMERIC_AVL_NODE_H

typedef struct BalancedTreeNode BalancedTreeNode;

BalancedTreeNode* createBalancedTreeNode(int value);
void destroyBalancedTreeNode(BalancedTreeNode* node);

void destroyBalancedSubtree(BalancedTreeNode*);

#endif /* SPBU_2020_C_NUMERIC_AVL_NODE_H */
