#include <stdio.h>
#include <stdlib.h>

int comparison(const void* a, const void* b)
{
    return *(int*)b - *(int*)a;
}

int main()
{
    int numbers[] = { 1, 2, 3, 4, 3, 5, 1, 1, 2 };
    int numbersLength = sizeof(numbers) / sizeof(int);

    qsort(numbers, numbersLength, sizeof(int), comparison);

    int lastNumber = numbers[0];
    for (int i = 1; i < numbersLength; i++) {
        if (numbers[i] == lastNumber) {
            printf("%d\n", numbers[i]);
            break;
        } else
            lastNumber = numbers[i];
    }

    return 0;
}
