#include "operations.h"

int min(int a, int b)
{
    return a > b ? b : a;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(int* array, int size)
{
    int limit = size / 2;
    for (int i = 0; i < limit; ++i) {
        swap(&array[i], &array[size - 1 - i]);
    }
}
