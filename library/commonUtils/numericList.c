#include "numericList.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct ListElement {
    int value;
    ListElement next;
};

struct List {
    ListElement head;
    ListElement tail;
    int length;
};

ListElement createListElement(int value)
{
    ListElement elem = malloc(sizeof(struct ListElement));
    elem->value = value;
    elem->next = NULL;
    return elem;
}

List createList()
{
    List list = malloc(sizeof(struct List));
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    return list;
}

List shift(List list, ListElement elem)
{
    if (!list->head) {
        list->head = elem;
        list->tail = elem;
    } else {
        elem->next = list->head;
        list->head = elem;
    }
    list->length++;
    return list;
}

List push(List list, ListElement elem)
{
    if (!list->tail) {
        list->head = elem;
        list->tail = elem;
    } else {
        list->tail->next = elem;
        list->tail = elem;
    }
    list->tail->next = NULL;
    list->length++;
    return list;
}

ListElement getListElementByIndex(List list, int index)
{
    if (index >= list->length || index < 0)
        return NULL;
    if (index == list->length - 1)
        return list->tail;

    ListElement found = list->head;
    for (int i = 0; i < index; i++) {
        found = found->next;
    }
    return found;
}

int getValue(ListElement elem)
{
    if (!elem)
        return 0;
    return elem->value;
}

int getLength(List list)
{
    return list->length;
}

bool unshift(List list)
{
    ListElement toDelete = list->head;
    if (!toDelete)
        return false;
    int temp = toDelete->value;

    list->head = toDelete->next;
    if (!list->head)
        list->tail == NULL;

    list->length--;
    free(toDelete);
    return true;
}

bool pop(List list)
{
    ListElement prevToDelete = getListElementByIndex(list, list->length - 2);
    if (!prevToDelete) { // length 0-1
        if (!list->tail) { // length 0
            return false;
        }

        // length 1
        ListElement toDelete = list->tail;
        list->head = NULL;
        list->tail = NULL;
        list->length--;
        free(toDelete);
        return true;
    }

    ListElement toDelete = list->tail;
    list->tail = prevToDelete;
    list->tail->next = NULL;
    list->length--;
    free(toDelete);
    return true;
}

void destroyList(List list)
{
    while (unshift(list)) { };
    free(list);
}

void printList(List list)
{
    ListElement elem = list->head;
    while (elem) {
        printf("%d\n", elem->value);
        elem = elem->next;
    }
}
