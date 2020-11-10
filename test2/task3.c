#include "../library/numeric/io.h"
#include "../library/numeric/list.h"
#include <stdio.h>

int main()
{
    int a = 0;
    int b = 0;

    promptInt("a: ", &a);
    promptInt("b: ", &b);

    FILE* filePointer = fopen("numbersab.txt", "r");

    if (filePointer == NULL) {
        printf("Make sure numbersab.txt is available in the working directory.\n");
        return 0;
    }

    List* listA = createList();
    List* listAB = createList();
    List* listB = createList();

    int d = 0;

    while (!feof(filePointer)) {
        fscanf(filePointer, "%d", &d);
        ListElement* element = createListElement(d);
        if (d < a) {
            insert(listA, getLength(listA), element);
        } else if (d >= a && d <= b) {
            insert(listAB, getLength(listAB), element);
        } else {
            insert(listB, getLength(listB), element);
        }
    }

    printList("Less than a: ", listA);
    printList("Between a and b: ", listAB);
    printList("Larger than b: ", listB);

    destroyList(&listA);
    destroyList(&listAB);
    destroyList(&listB);

    fclose(filePointer);
    return 0;
}
