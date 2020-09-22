#ifndef SPBU_2020_C_NUMERICLIST_H
#define SPBU_2020_C_NUMERICLIST_H

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
int getLength(List list);

void printList(List);

#endif //SPBU_2020_C_NUMERICLIST_H
