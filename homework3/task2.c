#include "../library/numeric/io.h"
#include "../library/numeric/list.h"
#include <stdio.h>

int main()
{
    int n = 0;
    promptInt("Number of warriors: ", &n);
    int m = 0;
    promptInt("Kill every: ", &m);

    ListI* warriors = createListI();
    makeCycleI(warriors);

    for (int i = n; i > 0; --i) {
        ListElementI* warrior = createListElementI(i);
        insertElementI(warriors, 0, warrior);
    }

    ListElementI* prevToKill = getTailI(warriors);
    while (getLengthI(warriors) > m - 1) {
        for (int i = 0; i < m - 1; ++i)
            prevToKill = getNextElementI(prevToKill);
        int toKillPosition = locateElementI(warriors, getNextElementI(prevToKill));
        removeElementI(warriors, toKillPosition);
    }

    printf("Remaining warriors: ");
    printListI(warriors);

    destroyListI(warriors);

    return 0;
}
