#include "avl_balancing.h"
#include "../../operations.h"
#include "avl_structure.h"
#include <stdlib.h>

int getHeight(BalancedTreeNode* node)
{
    return (node == NULL) ? 0 : node->height;
}

int getBalanceFactor(BalancedTreeNode* node)
{
    return (node == NULL) ? 0 : getHeight(node->rightChild) - getHeight(node->leftChild);
}

void updateHeightBalancedTreeNode(BalancedTreeNode* node)
{
    if (node == NULL)
        return;
    int leftHeight = getHeight(node->leftChild);
    int rightHeight = getHeight(node->rightChild);
    node->height = max(leftHeight, rightHeight) + 1;
}

void rotateLeft(BalancedTreeNode** nodePtr)
{
    if (nodePtr == NULL || *nodePtr == NULL)
        return;
    BalancedTreeNode* node = *nodePtr;
    BalancedTreeNode* temp = node->rightChild;
    node->rightChild = node->rightChild->leftChild;
    temp->leftChild = node;
    updateHeightBalancedTreeNode(node);
    updateHeightBalancedTreeNode(temp);
    *nodePtr = temp;
}

void rotateRight(BalancedTreeNode** nodePtr)
{
    if (nodePtr == NULL || *nodePtr == NULL)
        return;
    BalancedTreeNode* node = *nodePtr;
    BalancedTreeNode* temp = node->leftChild;
    node->leftChild = node->leftChild->rightChild;
    temp->rightChild = node;
    updateHeightBalancedTreeNode(node);
    updateHeightBalancedTreeNode(temp);
    *nodePtr = temp;
}

void balanceTreeFromNode(BalancedTreeNode** nodePtr)
{
    BalancedTreeNode* node = *nodePtr;
    if (getBalanceFactor(node) == 2) {
        if (getBalanceFactor(node->rightChild) < 0)
            rotateRight(&(node->rightChild));
        rotateLeft(&node);
    }
    if (getBalanceFactor(node) == -2) {
        if (getBalanceFactor(node->leftChild) > 0)
            rotateLeft(&(node->leftChild));
        rotateRight(&node);
    }
    *nodePtr = node;
}

int updateHeightAndBalanceSubtree(BalancedTreeNode** nodePtr, int addedOrRemovedValue)
{
    if (nodePtr == NULL || *nodePtr == NULL)
        return 0;

    BalancedTreeNode* node = *nodePtr;

    if (addedOrRemovedValue < node->value) {
        int updatedLeftChildHeight = updateHeightAndBalanceSubtree(&(node->leftChild), addedOrRemovedValue);
        node->height = max(updatedLeftChildHeight, getHeight(node->rightChild)) + 1;
    } else {
        int updatedRightChildHeight = updateHeightAndBalanceSubtree(&(node->rightChild), addedOrRemovedValue);
        int leftChildHeight = getHeight(node->leftChild);

        // This is needed for counting correct height after removing a node with 2 children.
        if (node->rightChild != NULL && addedOrRemovedValue < node->rightChild->value)
            leftChildHeight = updateHeightAndBalanceSubtree(&(node->leftChild), addedOrRemovedValue);

        node->height = max(leftChildHeight, updatedRightChildHeight) + 1;
    }

    balanceTreeFromNode(nodePtr);

    return node->height;
}
