#include "list.h"
#include <stdio.h>
#include <stdlib.h>

struct List {
    ListElement* first;
    ListElement* last;
    int length;
};

struct ListElement {
    int value;
    ListElement* next;
};

List* createList()
{
    List* list = (List*)malloc(sizeof(List));
    list->first = NULL;
    list->last = NULL;
    list->length = 0;
    return list;
}

int getLength(List* list)
{
    if (list == NULL)
        return 0;
    return list->length;
}

ListElement* getFirstElement(List* list)
{
    if (list == NULL)
        return NULL;
    return list->first;
}

ListElement* getLastElement(List* list)
{
    if (list == NULL)
        return NULL;
    return list->last;
}

bool destroyList(List** list)
{
    if (list == NULL || *list == NULL)
        return false;

    bool ejectedSuccessfully = eject(*list, 0);
    while (ejectedSuccessfully)
        ejectedSuccessfully = eject(*list, 0);

    free(*list);
    *list = NULL;

    return true;
}

ListElement* createListElement(int value)
{
    ListElement* element = (ListElement*)malloc(sizeof(ListElement));
    element->value = value;
    element->next = NULL;
    return element;
}

int getElementValue(ListElement* element)
{
    if (element == NULL)
        return 0;
    return element->value;
}

bool setElementValue(ListElement* element, int value)
{
    if (element == NULL)
        return false;
    element->value = value;
    return true;
}

ListElement* getNextElement(ListElement* element)
{
    if (element == NULL)
        return NULL;
    return element->next;
}

bool insert(List* list, int index, ListElement* element)
{
    if (list == NULL || element == NULL
        || index < 0 || index > getLength(list))
        return false;

    ListElement* elementBefore = NULL;
    ListElement* elementAfter = NULL;

    if (index == getLength(list)) {
        elementBefore = getLastElement(list);
        elementAfter = NULL;
    } else {
        elementBefore = NULL;
        elementAfter = getFirstElement(list);
        for (int i = 0; i < index; ++i) {
            elementBefore = elementAfter;
            elementAfter = getNextElement(elementAfter);
        }
    }

    if (elementBefore != NULL)
        elementBefore->next = element;
    if (index == 0)
        list->first = element;

    element->next = elementAfter;
    if (index == getLength(list))
        list->last = element;

    list->length++;

    return true;
}

ListElement* retrieve(List* list, int index)
{
    if (list == NULL
        || index < 0 || index >= getLength(list))
        return NULL;

    if (index == getLength(list) - 1)
        return getLastElement(list);

    ListElement* element = getFirstElement(list);
    for (int i = 0; i < index; ++i)
        element = getNextElement(element);

    return element;
}

int locate(List* list, ListElement* element)
{
    if (list == NULL || element == NULL)
        return -1;

    if (element == getLastElement(list))
        return getLength(list) - 1;

    int index = 0;
    ListElement* elementToCompare = getFirstElement(list);
    while (element != elementToCompare && index < list->length) {
        elementToCompare = getNextElement(elementToCompare);
        index++;
    }

    if (index == getLength(list))
        return -1;
    return index;
}

bool eject(List* list, int index)
{
    if (list == NULL
        || index < 0 || index >= getLength(list))
        return false;

    ListElement* elementBefore = NULL;
    ListElement* elementToDelete = getFirstElement(list);
    ListElement* elementAfter = getNextElement(elementToDelete);
    for (int i = 0; i < index; ++i) {
        elementBefore = elementToDelete;
        elementToDelete = elementAfter;
        elementAfter = getNextElement(elementAfter);
    }

    if (elementBefore != NULL)
        elementBefore->next = elementAfter;
    if (index == 0)
        list->first = elementAfter;
    if (index == getLength(list) - 1)
        list->last = elementBefore;

    free(elementToDelete);

    list->length--;

    return true;
}

void printList(char prefix[], List* list)
{
    printf("%s", prefix);
    ListElement* element = getFirstElement(list);
    for (int i = 0; i < getLength(list); ++i) {
        printf("%d ", getElementValue(element));
        element = getNextElement(element);
    }
    printf("\n");
}
