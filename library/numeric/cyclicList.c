#include "cyclicList.h"
#include <stdlib.h>

void setCycle(List* list)
{
    ListElement* firstElement = getFirstElement(list);
    ListElement* lastElement = getLastElement(list);
    if (lastElement != NULL)
        _setNextElement(lastElement, firstElement);
}

bool insertCyclic(List* list, int index, ListElement* element)
{
    bool insertResult = insert(list, index, element);
    if (insertResult && (index == 0 || index == getLength(list) - 1))
        setCycle(list);
    return insertResult;
}

bool ejectCyclic(List* list, int index)
{
    bool ejectResult = eject(list, index);
    if (ejectResult && (index == 0 || index == getLength(list)))
        setCycle(list);
    return ejectResult;
}
