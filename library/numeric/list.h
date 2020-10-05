#pragma once
#include <stdbool.h>

// "I" for integer

typedef struct ListI ListI;
typedef struct ListElementI ListElementI;

ListI* createListI();
ListElementI* createListElementI(int value);

ListElementI* getHeadI(ListI*);
ListElementI* getTailI(ListI*);
int getLengthI(ListI*);
ListElementI* getElementI(ListI*, int position);
int getElementValueI(ListElementI*);
void setElementValueI(ListElementI*, int value);
bool insertElementI(ListI*, int position, ListElementI*);
int locateElementI(ListI*, ListElementI*);
int locateElementByValueI(ListI*, int value);

bool removeElementI(ListI*, int position);
bool destroyListI(ListI*);
