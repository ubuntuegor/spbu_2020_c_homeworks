#include "bst_operations.h"
#include "../bst_node.h"
#include "bst_structure.h"
#include <stdio.h>
#include <stdlib.h>

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

bool insertIntoBinarySubtree(BinaryTreeNode* node, int value)
{
    if (node == NULL)
        return false;

    bool nodeToInsertIsFound = false;
    while (!nodeToInsertIsFound) {
        if (value == node->value)
            return false;
        if (value < node->value) {
            if (node->leftChild != NULL)
                node = node->leftChild;
            else
                nodeToInsertIsFound = true;
        } else {
            if (node->rightChild != NULL)
                node = node->rightChild;
            else
                nodeToInsertIsFound = true;
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
    while (replaceNode->rightChild != NULL)
        replaceNode = replaceNode->rightChild;

    return replaceNode;
}

bool removeFromBinarySubtree(BinaryTreeNode** nodePtr, int value)
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
        removeFromBinarySubtree(&toDelete, replaceValue);
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

void destroyBinarySubtree(BinaryTreeNode* node)
{
    if (node == NULL)
        return;
    destroyBinarySubtree(node->leftChild);
    destroyBinarySubtree(node->rightChild);
    free(node);
}
