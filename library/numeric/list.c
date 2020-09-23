#include "list.h"
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

ListElement unshift(List list)
{
    ListElement toDelete = list->head;
    if (!toDelete)
        return NULL;
    int temp = toDelete->value;

    list->head = toDelete->next;
    if (!list->head)
        list->tail == NULL;

    list->length--;
    // free(toDelete);
    return toDelete;
}

ListElement pop(List list)
{
    ListElement prevToDelete = getListElementByIndex(list, list->length - 2);
    if (!prevToDelete) {
        if (!list->tail) {
            return NULL;
        }

        ListElement toDelete = list->tail;
        list->head = NULL;
        list->tail = NULL;
        list->length--;
        // free(toDelete);
        return toDelete;
    }

    ListElement toDelete = list->tail;
    list->tail = prevToDelete;
    list->tail->next = NULL;
    list->length--;
    // free(toDelete);
    return toDelete;
}

void destroyList(List list)
{
    ListElement toFree;
    while (toFree = unshift(list))
        free(toFree);
    free(list);
}

void printList(List list, char* separator)
{
    ListElement elem = list->head;
    while (elem) {
        printf("%d%s", elem->value, separator);
        elem = elem->next;
    }
}
