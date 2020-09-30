#include "../library/numeric/operations.h"
#include <stdio.h>
#include <stdlib.h>

int comparison(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

void promptLLU(char prompt[], unsigned long long* variablePtr)
{
    printf(prompt);
    scanf("%llu", variablePtr);
}

void printArrayAsNumber(int array[], int length)
{
    for (int i = 0; i < length; i++)
        printf("%d", array[i]);
    printf("\n");
}

void getMinimalNumberFromDigits(int digits[], int digitsLength)
{
    qsort(digits, digitsLength, sizeof(int), comparison);

    int firstNonZero = 0;
    while (firstNonZero < digitsLength && digits[firstNonZero] == 0)
        firstNonZero++;
    swap(&digits[0], &digits[firstNonZero]);
}

int main()
{
    unsigned long long number = 0;
    promptLLU("Enter a number: ", &number);

    if (number < 0) {
        printf("Number must not be negative.\n");
        return 0;
    }

    int digitsLength = countDigits(number);
    int* digits = (int*)calloc(digitsLength, sizeof(int));
    dissectNumberToDigits(digits, digitsLength, number);
    getMinimalNumberFromDigits(digits, digitsLength);

    printf("Result: ");
    printArrayAsNumber(digits, digitsLength);
    free(digits);

    return 0;
}
