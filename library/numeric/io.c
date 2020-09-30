#include "io.h"
#include <stdio.h>

void promptInt(char prompt[], int* variablePtr)
{
    printf(prompt);
    scanf("%d", variablePtr);
}

void promptIntArray(char prompt[], int array[], int length)
{
    printf(prompt);
    for (int i = 0; i < length; ++i)
        scanf("%d", &array[i]);
}

void printIntArray(int array[], int length)
{
    for (int i = 0; i < length; ++i)
        printf("%d ", array[i]);
    printf("\n");
}
