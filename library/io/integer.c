#include <stdio.h>

void promptInt(char prompt[], int* variablePtr)
{
    printf(prompt);
    scanf("%d", variablePtr);
}

void printIntArray(int array[], int length)
{
    for (int i = 0; i < length; ++i)
        printf("%d ", array[i]);
    printf("\n");
}
