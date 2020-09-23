#include "../library/numeric/list.h"
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

    List buffer = createList();

    char* numChar = strtok(inputString, " ");
    do {
        ListElement elem = createListElement(atoi(numChar));
        push(buffer, elem);
    } while (numChar = strtok(NULL, " "));

    int numbersLength = getLength(buffer);
    int* numbers = calloc(numbersLength, sizeof(int));
    for (int i = 0; i < numbersLength; i++) {
        ListElement elem = unshift(buffer);
        numbers[i] = getValue(elem);
        free(elem);
    }
    destroyList(buffer);

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
