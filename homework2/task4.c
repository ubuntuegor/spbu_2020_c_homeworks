#include "../library/numeric/operations.h"
#include <stdio.h>
#include <stdlib.h>

int comparison(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int main()
{
    int number = 0;
    printf("Enter a number: ");
    scanf("%d", &number);

    if (number < 0) {
        printf("Number must not be negative.\n");
        return 0;
    }

    int digitsCount = countDigits(number);
    int* digits = (int*)calloc(digitsCount, sizeof(int));
    dissectNumberToDigits(digits, digitsCount, number);

    qsort(digits, digitsCount, sizeof(int), comparison);

    int firstNonZero = 0;
    while (firstNonZero < digitsCount && digits[firstNonZero] == 0)
        firstNonZero++;
    swap(&digits[0], &digits[firstNonZero]);

    printf("Result: ");
    for (int i = 0; i < digitsCount; i++)
        printf("%d", digits[i]);
    printf("\n");

    free(digits);

    return 0;
}
