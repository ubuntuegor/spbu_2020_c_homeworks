#include "../library/numeric/list.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    ListElement elem1 = createListElement(1);
    ListElement elem2 = createListElement(2);
    ListElement elem3 = createListElement(3);
    ListElement elem4 = createListElement(4);
    ListElement elem5 = createListElement(5);
    List list = createList();
    push(list, elem2); // 2
    push(list, elem3); // 2, 3
    shift(list, elem4); // 4, 2, 3
    unshift(list); // 2, 3
    shift(list, elem1); // 1, 2, 3
    push(list, elem5); // 1, 2, 3, 5
    pop(list); // 1, 2, 3
    push(list, elem4); // 1, 2, 3, 4
    push(list, elem5); // 1, 2, 3, 4, 5

    printf("List:\n");
    printList(list, " ");
    printf("\n");
    printf("Length: %d\n", getLength(list));
    destroyList(list);
    return 0;
}
