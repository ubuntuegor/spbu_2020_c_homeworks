#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int stringLimit = 1000;

int comparison(const void* a, const void* b)
{
    return *(int*)b - *(int*)a;
}

int main()
{
    char inputString[stringLimit];
    for (int i = 0; i < stringLimit; i++) {
        inputString[i] = '\0';
    }

    printf("Enter numbers separated with spaces: ");
    fgets(inputString, stringLimit, stdin);

    int numbersLength = 0;
    int* numbers = (int*)malloc(sizeof(int));
    numbers[0] = 0;

    char* numChar = strtok(inputString, " ");
    while (numChar) {
        numbersLength++;
        numbers = realloc(numbers, numbersLength * sizeof(int));
        numbers[numbersLength - 1] = atoi(numChar);
        numChar = strtok(NULL, " ");
    }

    qsort(numbers, numbersLength, sizeof(int), comparison);

    bool success = false;
    int lastNumber = numbers[0];
    for (int i = 1; i < numbersLength; i++) {
        if (numbers[i] == lastNumber) {
            success = true;
            printf("Result: %d\n", numbers[i]);
            break;
        } else
            lastNumber = numbers[i];
    }
    free(numbers);

    if (!success)
        printf("All numbers are unique!\n");

    return 0;
}
