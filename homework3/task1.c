#include "../library/numeric/list.h"
#include <stdio.h>

int main()
{
    ListI* list = createListI();
    ListElementI* element1 = createListElementI(1);
    ListElementI* element2 = createListElementI(2);
    ListElementI* element3 = createListElementI(3);
    ListElementI* element4 = createListElementI(4);

    insertElementI(list, 0, element2);
    insertElementI(list, 1, element4);
    insertElementI(list, 0, element1);
    insertElementI(list, 2, element3);

    printf("List: ");
    printListI(list);
    printf("Length: %d\n", getLengthI(list));

    int somePosition = locateElementI(list, element3);
    printf("Element 3 index: %d\n", somePosition);

    ListElementI* someElement = getElementI(list, somePosition);
    printf("Value of element by index %d: %d\n", somePosition, getElementValueI(someElement));
    printf("This element equals element 3: %s\n", (someElement == element3) ? "true" : "false");

    setElementValueI(someElement, 10);
    removeElementI(list, 3);

    printf("New list: ");
    printListI(list);
    printf("Length: %d\n", getLengthI(list));

    destroyListI(list);

    return 0;
}
