#include <stdio.h>

void promptInt(char prompt[], int* variablePtr)
{
    printf(prompt);
    scanf("%d", variablePtr);
}
