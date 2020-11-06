#include "avl_balancing.h"
#include "../../operations.h"
#include "avl_structure.h"
#include <stdlib.h>

int getHeight(BinaryTreeNode* node)
{
    return (node == NULL) ? 0 : node->height;
}

int getBalanceFactor(BinaryTreeNode* node)
{
    return (node == NULL) ? 0 : getHeight(node->rightChild) - getHeight(node->leftChild);
}

void updateHeightBinaryTreeNode(BinaryTreeNode* node)
{
    if (node == NULL)
        return;
    int leftHeight = getHeight(node->leftChild);
    int rightHeight = getHeight(node->rightChild);
    node->height = max(leftHeight, rightHeight) + 1;
}

void rotateLeft(BinaryTreeNode** nodePtr)
{
    if (nodePtr == NULL || *nodePtr == NULL)
        return;
    BinaryTreeNode* node = *nodePtr;
    BinaryTreeNode* temp = node->rightChild;
    node->rightChild = node->rightChild->leftChild;
    temp->leftChild = node;
    updateHeightBinaryTreeNode(node);
    updateHeightBinaryTreeNode(temp);
    *nodePtr = temp;
}

void rotateRight(BinaryTreeNode** nodePtr)
{
    if (nodePtr == NULL || *nodePtr == NULL)
        return;
    BinaryTreeNode* node = *nodePtr;
    BinaryTreeNode* temp = node->leftChild;
    node->leftChild = node->leftChild->rightChild;
    temp->rightChild = node;
    updateHeightBinaryTreeNode(node);
    updateHeightBinaryTreeNode(temp);
    *nodePtr = temp;
}

void balanceTreeFromNode(BinaryTreeNode** nodePtr)
{
    BinaryTreeNode* node = *nodePtr;
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

int updateHeightAndBalanceBinarySubtree(BinaryTreeNode** nodePtr, int addedOrRemovedValue)
{
    if (nodePtr == NULL || *nodePtr == NULL)
        return 0;

    BinaryTreeNode* node = *nodePtr;

    if (addedOrRemovedValue < node->value) {
        int updatedLeftChildHeight = updateHeightAndBalanceBinarySubtree(&(node->leftChild), addedOrRemovedValue);
        node->height = max(updatedLeftChildHeight, getHeight(node->rightChild)) + 1;
    } else {
        int updatedRightChildHeight = updateHeightAndBalanceBinarySubtree(&(node->rightChild), addedOrRemovedValue);
        int leftChildHeight = getHeight(node->leftChild);

        // This is needed for counting correct height after removing a node with 2 children.
        if (node->rightChild != NULL && addedOrRemovedValue < node->rightChild->value)
            leftChildHeight = updateHeightAndBalanceBinarySubtree(&(node->leftChild), addedOrRemovedValue);

        node->height = max(leftChildHeight, updatedRightChildHeight) + 1;
    }

    balanceTreeFromNode(nodePtr);

    return node->height;
}
