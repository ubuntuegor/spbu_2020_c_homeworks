#ifndef SPBU_2020_C_NUMERIC_LIST_H
#define SPBU_2020_C_NUMERIC_LIST_H

#include <stdbool.h>

typedef struct List List;
typedef struct ListElement ListElement;

List* createList();
int getLength(List*);
ListElement* getFirstElement(List*);
ListElement* getLastElement(List*);
bool destroyList(List**);

ListElement* createListElement(int value);
int getElementValue(ListElement*);
bool setElementValue(ListElement*, int value);
ListElement* getNextElement(ListElement*);
ListElement* getNextElementInCycle(ListElement*, List*);
void destroyListElement(ListElement**);

bool insert(List*, int index, ListElement*);
ListElement* retrieve(List*, int index);
int locate(List*, ListElement*);
bool eject(List*, int index);

void printList(char prefix[], List*);

#endif /* SPBU_2020_C_NUMERIC_LIST_H */
