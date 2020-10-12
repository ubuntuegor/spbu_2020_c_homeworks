#include "../library/numeric/io.h"
#include "../library/numeric/list.h"
#include <stdio.h>

List* createWarriors(int number)
{
    List* warriors = createList();

    for (int i = number; i > 0; --i) {
        ListElement* warrior = createListElement(i);
        insert(warriors, 0, warrior);
    }

    return warriors;
}

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

    List* warriors = createWarriors(n);

    ListElement* prevToKill = getLastElement(warriors);
    while (getLength(warriors) > 1) {
        for (int i = 0; i < m - 1; ++i)
            prevToKill = getNextElementInCycle(prevToKill, warriors);
        int toKillPosition = locate(warriors, getNextElementInCycle(prevToKill, warriors));
        eject(warriors, toKillPosition);
    }

    printf("Remaining warrior: %d\n", getElementValue(getFirstElement(warriors)));

    destroyList(&warriors);

    return 0;
}