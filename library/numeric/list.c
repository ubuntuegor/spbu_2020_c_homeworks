#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct ListI {
    ListElementI* head;
    ListElementI* tail;
    int length;
    bool cyclic;
};

struct ListElementI {
    int value;
    ListElementI* next;
};

ListI* createListI()
{
    ListI* list = (ListI*)malloc(sizeof(ListI));
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    list->cyclic = false;
    return list;
}

ListElementI* createListElementI(int value)
{
    ListElementI* element = (ListElementI*)malloc(sizeof(ListElementI));
    element->value = value;
    element->next = NULL;
    return element;
}

ListElementI* getHeadI(ListI* list)
{
    return list->head;
}

ListElementI* getTailI(ListI* list)
{
    return list->tail;
}

int getLengthI(ListI* list)
{
    return list->length;
}

ListElementI* getElementI(ListI* list, int position)
{
    if (position >= list->length)
        return NULL;
    if (position == list->length - 1)
        return list->tail;

    ListElementI* element = list->head;
    for (int i = 0; i < position; ++i) {
        element = element->next;
    }
    return element;
}

ListElementI* getNextElementI(ListElementI* element)
{
    return element->next;
}

int getElementValueI(ListElementI* element)
{
    return element->value;
}

void setElementValueI(ListElementI* element, int value)
{
    element->value = value;
}

bool insertElementI(ListI* list, int position, ListElementI* element)
{
    if (position > list->length)
        return false;

    ListElementI* prevElement = NULL;
    ListElementI* nextElement = list->head;
    for (int i = 0; i < position; ++i) {
        prevElement = nextElement;
        nextElement = prevElement->next;
    }

    if (position == 0) {
        list->head = element;
        if (list->cyclic) {
            if (list->tail)
                list->tail->next = element;
            else
                element->next = element;
        }
    } else {
        prevElement->next = element;
    }

    if (position == list->length)
        list->tail = element;

    element->next = nextElement;

    list->length++;

    return true;
}

int locateElementI(ListI* list, ListElementI* element)
{
    int position = 0;
    ListElementI* pointer = list->head;
    while (pointer != NULL && pointer != element) {
        ++position;
        pointer = pointer->next;
    }

    if (pointer == NULL)
        position = -1;

    return position;
}

int locateElementByValueI(ListI* list, int value)
{
    int position = 0;
    ListElementI* pointer = list->head;
    while (pointer != NULL && pointer->value != value) {
        ++position;
        pointer = pointer->next;
    }

    if (pointer == NULL)
        position = -1;

    return position;
}

void printListI(ListI* list)
{
    ListElementI* element = list->head;
    for (int i = 0; i < list->length; ++i) {
        printf("%d ", element->value);
        element = element->next;
    }
    printf("\n");
}

bool removeElementI(ListI* list, int position)
{
    if (position >= list->length)
        return false;

    ListElementI* prevElement = (list->cyclic) ? list->tail : NULL;
    ListElementI* element = list->head;
    for (int i = 0; i < position; ++i) {
        prevElement = element;
        element = prevElement->next;
    }

    if (position == 0) {
        list->head = element->next;
        if (list->cyclic)
            list->tail->next = element->next;
    } else {
        prevElement->next = element->next;
    }

    if (position == list->length - 1) {
        list->tail = prevElement;
        if (list->cyclic)
            prevElement->next = list->head;
    }

    free(element);
    list->length--;

    if (list->length == 0) {
        list->head = NULL;
        list->tail = NULL;
    }

    return true;
}

bool destroyListI(ListI* list)
{
    while (removeElementI(list, 0)) { }
    free(list);
    return true;
}

void makeCycleI(ListI* list)
{
    list->cyclic = true;
    if (list->tail)
        list->tail->next = list->head;
}

void breakCycleI(ListI* list)
{
    list->cyclic = false;
    if (list->tail)
        list->tail->next = NULL;
}

bool isCyclicI(ListI* list)
{
    return list->cyclic;
}
