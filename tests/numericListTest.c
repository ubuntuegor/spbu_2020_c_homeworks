#include "../library/commonUtils/numericList.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    ListElement elem1 = createListElement(1);
    ListElement elem2 = createListElement(2);
    ListElement elem3 = createListElement(3);
    List list = createList();
    push(list, elem2);
    push(list, elem3);
    shift(list, elem1);
    printf("%d %d %d\n", getValue(getListElementByIndex(list, 0)), getValue(getListElementByIndex(list, 1)), getValue(getListElementByIndex(list, 2)));

    printList(list);
    printf("%d\n", getLength(list));
    destroyList(list);
}
