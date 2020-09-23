#pragma once
#include <stdbool.h>

typedef struct ListElement* ListElement;

typedef struct List* List;

ListElement createListElement(int value);
List createList();

List shift(List, ListElement);
List push(List, ListElement);

ListElement unshift(List);
ListElement pop(List);
void destroyList(List);

ListElement getListElementByIndex(List, int);
int getValue(ListElement);
int getLength(List);

void printList(List, char* separator);
