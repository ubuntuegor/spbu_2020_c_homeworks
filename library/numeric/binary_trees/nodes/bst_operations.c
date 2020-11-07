#include "bst_operations.h"
#include "../bst_node.h"
#include "bst_structure.h"
#include <stdio.h>

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

bool existsInBinarySubtree(BinaryTreeNode* node, int value)
{
    while (node != NULL && node->value != value) {
        if (value < node->value)
            node = node->leftChild;
        else
            node = node->rightChild;
    }

    return node != NULL;
}

bool insertIntoBinarySubtree(BinaryTreeNode* node, BinaryTreeNode* nodeToInsert)
{
    if (node == NULL || nodeToInsert == NULL)
        return false;

    bool placeToInsertIsFound = false;
    while (!placeToInsertIsFound) {
        if (nodeToInsert->value == node->value)
            return false;
        if (nodeToInsert->value < node->value) {
            if (node->leftChild != NULL)
                node = node->leftChild;
            else
                placeToInsertIsFound = true;
        } else {
            if (node->rightChild != NULL)
                node = node->rightChild;
            else
                placeToInsertIsFound = true;
        }
    }

    if (nodeToInsert->value < node->value)
        node->leftChild = nodeToInsert;
    else
        node->rightChild = nodeToInsert;

    return true;
}

BinaryTreeNode* findReplacement(BinaryTreeNode* node)
{
    BinaryTreeNode* replaceNode = node->leftChild;
    while (replaceNode->rightChild != NULL)
        replaceNode = replaceNode->rightChild;

    return replaceNode;
}

bool removeFromBinarySubtree(BinaryTreeNode** nodePtr, int value, BinaryTreeNode** removedNodePtr)
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
        *removedNodePtr = toDelete;
    } else if (toDeleteChildrenCount == 1) {
        newNode = toDelete->leftChild;
        if (newNode == NULL)
            newNode = toDelete->rightChild;
        *removedNodePtr = toDelete;
    } else {
        BinaryTreeNode* replaceNode = findReplacement(toDelete);
        int replaceValue = replaceNode->value;
        removeFromBinarySubtree(&toDelete, replaceValue, removedNodePtr);
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

void printBinarySubtree(BinaryTreeNode* node)
{
    if (node == NULL) {
        printf("null");
        return;
    }

    printf("(%d ", node->value);
    printBinarySubtree(node->leftChild);
    printf(" ");
    printBinarySubtree(node->rightChild);
    printf(")");
}

void printAscendingBinarySubtree(BinaryTreeNode* node)
{
    if (node == NULL)
        return;
    printAscendingBinarySubtree(node->leftChild);
    printf("%d ", node->value);
    printAscendingBinarySubtree(node->rightChild);
}

void printDescendingBinarySubtree(BinaryTreeNode* node)
{
    if (node == NULL)
        return;
    printDescendingBinarySubtree(node->rightChild);
    printf("%d ", node->value);
    printDescendingBinarySubtree(node->leftChild);
}
