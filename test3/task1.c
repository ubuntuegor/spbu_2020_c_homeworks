#include "../library/numeric/hash_table/hash_table.h"
#include "../library/numeric/io.h"
#include <stdio.h>
#include <stdlib.h>

int compareHashElementsAscending(const void* a, const void* b)
{
    long long keyA = getHashElementKey(*(HashElement**)a);
    long long keyB = getHashElementKey(*(HashElement**)b);
    if (keyA > keyB)
        return 1;
    if (keyA < keyB)
        return -1;
    return 0;
}

void printOccurrences(HashTable* counterTable)
{
    HashElement** numbers = getHashTableAsArray(counterTable);
    qsort(numbers, getHashTableSize(counterTable), sizeof(HashElement*), compareHashElementsAscending);

    printf("Occurrences:\n");
    for (int i = 0; i < getHashTableSize(counterTable); ++i)
        printf("%lld: %d\n", getHashElementKey(numbers[i]), getHashElementValue(numbers[i]));

    destroyHashTableArray(numbers, getHashTableSize(counterTable));
}

int main()
{
    long long inputNumber;
    HashTable* counterTable = createHashTable();

    promptLL("Enter a sequence of whole numbers (0 to terminate): ", &inputNumber);

    while (inputNumber != 0) {
        int currentCount = 0;
        bool exists = getHashTableValue(counterTable, inputNumber, &currentCount);
        currentCount = exists ? currentCount + 1 : 1;
        setHashTableValue(counterTable, inputNumber, currentCount);
        promptLL("", &inputNumber);
    }

    printOccurrences(counterTable);

    destroyHashTable(&counterTable);

    return 0;
}
