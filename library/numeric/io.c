#include "io.h"
#include <stdio.h>

void promptInt(char prompt[], int* variablePtr)
{
    printf(prompt);
    scanf("%d", variablePtr);
}

void promptLL(char prompt[], long long* variablePtr)
{
    printf(prompt);
    scanf("%lld", variablePtr);
}

void promptULL(char prompt[], unsigned long long* variablePtr)
{
    printf(prompt);
    scanf("%llu", variablePtr);
}

void promptDouble(char prompt[], double* variablePtr)
{
    printf(prompt);
    scanf("%lf", variablePtr);
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

void printDoubleArray(double array[], int length)
{
    for (int i = 0; i < length; ++i)
        printf("%f ", array[i]);
    printf("\n");
}
