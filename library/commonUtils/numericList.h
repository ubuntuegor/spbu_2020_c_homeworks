#pragma once
#include <stdbool.h>

typedef struct ListElement* ListElement;

typedef struct List* List;

ListElement createListElement(int);
List createList();

List shift(List, ListElement);
List push(List, ListElement);

bool unshift(List);
bool pop(List);
void destroyList(List);

ListElement getListElementByIndex(List, int index);
int getValue(ListElement);
int getLength(List);

void printList(List);
