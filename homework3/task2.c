#include "../library/numeric/cyclicList.h"
#include "../library/numeric/io.h"
#include <stdio.h>

int main()
{
    int n = 0;
    promptInt("Number of warriors: ", &n);
    int m = 0;
    promptInt("Kill every: ", &m);

    if (n < 1 || m < 1) {
        printf("Invalid input\n");
        return 0;
    }

    List* warriors = createList();

    for (int i = n; i > 0; --i) {
        ListElement* warrior = createListElement(i);
        insertCyclic(warriors, 0, warrior);
    }

    ListElement* prevToKill = getLastElement(warriors);
    while (getLength(warriors) > 1) {
        for (int i = 0; i < m - 1; ++i)
            prevToKill = getNextElement(prevToKill);
        int toKillPosition = locate(warriors, getNextElement(prevToKill));
        ejectCyclic(warriors, toKillPosition);
    }

    printf("Remaining warrior: %d\n", getElementValue(getFirstElement(warriors)));

    destroyList(&warriors);

    return 0;
}