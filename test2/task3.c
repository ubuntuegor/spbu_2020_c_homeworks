#include "../library/numeric/io.h"
#include "../library/numeric/list.h"
#include <stdio.h>

void writeListToFile(FILE* filePointer, List* list)
{
    ListElement* element = getFirstElement(list);
    for (int i = 0; i < getLength(list); ++i) {
        fprintf(filePointer, "%d ", getElementValue(element));
        element = getNextElement(element);
    }
}

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

    fclose(filePointer);

    FILE* resultFilePointer = fopen("numbersabresult.txt", "w");

    writeListToFile(resultFilePointer, listA);
    writeListToFile(resultFilePointer, listAB);
    writeListToFile(resultFilePointer, listB);

    destroyList(&listA);
    destroyList(&listAB);
    destroyList(&listB);

    fclose(resultFilePointer);

    return 0;
}
