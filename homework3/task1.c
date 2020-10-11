#include "../library/numeric/list.h"
#include <stdio.h>

int main()
{
    List* list = createList();
    ListElement* element1 = createListElement(1);
    ListElement* element2 = createListElement(2);
    ListElement* element3 = createListElement(3);
    ListElement* element4 = createListElement(4);

    insert(list, 0, element2);
    insert(list, 1, element4);
    insert(list, 0, element1);
    insert(list, 2, element3);

    printList("List: ", list);
    printf("Length: %d\n", getLength(list));

    int somePosition = locate(list, element3);
    printf("Element 3 index: %d\n", somePosition);

    ListElement* someElement = retrieve(list, somePosition);
    printf("Value of element by index %d: %d\n", somePosition, getElementValue(someElement));
    printf("This element equals element 3: %s\n", (someElement == element3) ? "true" : "false");

    setElementValue(someElement, 10);
    eject(list, 3);

    printList("New list: ", list);

    destroyList(&list);

    return 0;
}
