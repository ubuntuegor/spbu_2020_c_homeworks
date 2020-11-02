#include "bst_node.h"
#include "../operations.h"
#include <stdio.h>
#include <stdlib.h>

struct BinaryTreeNode {
    int value;
    int height;
    BinaryTreeNode* leftChild;
    BinaryTreeNode* rightChild;
};

BinaryTreeNode* createBinaryTreeNode(int value)
{
    BinaryTreeNode* node = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    node->value = value;
    node->height = 0;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

int getChildrenCountBinaryTreeNode(BinaryTreeNode* node)
{
    if (node->leftChild == NULL && node->rightChild == NULL)
        return 0;
    else if (node->leftChild != NULL && node->rightChild != NULL)
        return 2;
    else
        return 1;
}

int getValueBinaryTreeNode(BinaryTreeNode* node)
{
    return (node == NULL) ? 0 : node->value;
}

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

int updateHeightAndBalanceBinaryTreeNode(BinaryTreeNode** nodePtr, int addedOrRemovedValue)
{
    if (nodePtr == NULL || *nodePtr == NULL)
        return 0;

    BinaryTreeNode* node = *nodePtr;

    if (addedOrRemovedValue < node->value) {
        int updatedLeftChildHeight = updateHeightAndBalanceBinaryTreeNode(&(node->leftChild), addedOrRemovedValue);
        node->height = max(updatedLeftChildHeight, getHeight(node->rightChild)) + 1;
    } else {
        int updatedRightChildHeight = updateHeightAndBalanceBinaryTreeNode(&(node->rightChild), addedOrRemovedValue);
        int leftChildHeight = getHeight(node->leftChild);

        // This is needed for counting correct height after removing a node with 2 children.
        if (node->rightChild != NULL && addedOrRemovedValue < node->rightChild->value)
            leftChildHeight = updateHeightAndBalanceBinaryTreeNode(&(node->leftChild), addedOrRemovedValue);

        node->height = max(leftChildHeight, updatedRightChildHeight) + 1;
    }

    balanceTreeFromNode(nodePtr);

    return node->height;
}

bool existsInBinaryTreeFromNode(BinaryTreeNode* node, int value)
{
    while (node != NULL && node->value != value) {
        if (value < node->value)
            node = node->leftChild;
        else
            node = node->rightChild;
    }

    return node != NULL;
}

bool insertIntoBinaryTreeFromNode(BinaryTreeNode* node, int value)
{
    if (node == NULL)
        return false;

    bool foundNodeToInsert = false;
    while (!foundNodeToInsert) {
        if (value == node->value)
            return false;
        if (value < node->value) {
            if (node->leftChild != NULL)
                node = node->leftChild;
            else
                foundNodeToInsert = true;
        } else {
            if (node->rightChild != NULL)
                node = node->rightChild;
            else
                foundNodeToInsert = true;
        }
    }

    if (value < node->value)
        node->leftChild = createBinaryTreeNode(value);
    else
        node->rightChild = createBinaryTreeNode(value);

    return true;
}

BinaryTreeNode* findReplacement(BinaryTreeNode* node)
{
    BinaryTreeNode* replaceNode = node->leftChild;
    while (replaceNode->rightChild != NULL) {
        replaceNode = replaceNode->rightChild;
    }
    return replaceNode;
}

bool removeFromBinaryTreeFromNode(BinaryTreeNode** nodePtr, int value)
{
    if (nodePtr == NULL || *nodePtr == NULL)
        return false;

    bool foundNodesToDelete = false;
    BinaryTreeNode* parentNode = NULL;
    BinaryTreeNode* toDelete = *nodePtr;

    while (!foundNodesToDelete) {
        if (value == toDelete->value)
            foundNodesToDelete = true;
        else if (value < toDelete->value) {
            if (toDelete->leftChild == NULL)
                return false;
            else {
                parentNode = toDelete;
                toDelete = toDelete->leftChild;
            }
        } else {
            if (toDelete->rightChild == NULL)
                return false;
            else {
                parentNode = toDelete;
                toDelete = toDelete->rightChild;
            }
        }
    }

    BinaryTreeNode* newNode = NULL;
    int toDeleteChildrenCount = getChildrenCountBinaryTreeNode(toDelete);

    if (toDeleteChildrenCount == 0) {
        newNode = NULL;
        free(toDelete);
    } else if (toDeleteChildrenCount == 1) {
        newNode = toDelete->leftChild;
        if (newNode == NULL)
            newNode = toDelete->rightChild;
        free(toDelete);
    } else {
        BinaryTreeNode* replaceNode = findReplacement(toDelete);
        int replaceValue = replaceNode->value;
        removeFromBinaryTreeFromNode(&toDelete, replaceValue);
        toDelete->value = replaceValue;
        newNode = toDelete;
    }

    if (parentNode != NULL) {
        if (value < parentNode->value)
            parentNode->leftChild = newNode;
        else
            parentNode->rightChild = newNode;
    } else {
        *nodePtr = newNode;
    }

    return true;
}

void printBinaryTreeFromNode(BinaryTreeNode* node)
{
    if (node == NULL) {
        printf("null");
        return;
    }

    printf("(%d ", node->value);
    printBinaryTreeFromNode(node->leftChild);
    printf(" ");
    printBinaryTreeFromNode(node->rightChild);
    printf(")");
}

void printAscendingBinaryTreeFromNode(BinaryTreeNode* node)
{
    if (node == NULL)
        return;
    printAscendingBinaryTreeFromNode(node->leftChild);
    printf("%d ", node->value);
    printAscendingBinaryTreeFromNode(node->rightChild);
}

void printDescendingBinaryTreeFromNode(BinaryTreeNode* node)
{
    if (node == NULL)
        return;
    printDescendingBinaryTreeFromNode(node->rightChild);
    printf("%d ", node->value);
    printDescendingBinaryTreeFromNode(node->leftChild);
}

void destroyBinaryTreeFromNode(BinaryTreeNode* node)
{
    if (node == NULL)
        return;
    destroyBinaryTreeFromNode(node->leftChild);
    destroyBinaryTreeFromNode(node->rightChild);
    free(node);
}
