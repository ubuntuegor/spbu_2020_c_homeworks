#pragma once
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

bool insert(List*, int index, ListElement*);
ListElement* retrieve(List*, int index);
int locate(List*, ListElement*);
bool remove(List*, int index);

void printList(List*, char prefix[]);
