#include "operations.h"
#include <math.h>

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

int binpow(int a, int n)
{
    int result = 1;
    while (n)
        if (n & 1) {
            result *= a;
            --n;
        } else {
            a *= a;
            n >>= 1;
        }
    return result;
}

void reverse(int array[], int size)
{
    int limit = size / 2;
    for (int i = 0; i < limit; ++i)
        swap(&array[i], &array[size - 1 - i]);
}

int countDigits(unsigned long long number)
{
    if (number == 0)
        return 1;
    return (int)log10(number) + 1;
}

void dissectNumberToDigits(int digitsArray[], int size, unsigned long long number)
{
    int i = size - 1;
    while (i >= 0) {
        digitsArray[i] = number % 10;
        number /= 10;
        --i;
    }
}
