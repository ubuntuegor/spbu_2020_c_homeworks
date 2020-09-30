#include "../library/numeric/io.h"
#include "../library/numeric/operations.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void printAllNumberDecompositions(int number, int limit, int prefix[], int prefixLength)
{
    // Allocate memory on first run.
    bool haveToDeallocate = false;
    if (prefix == NULL) {
        prefixLength = 0;
        prefix = (int*)calloc(number, sizeof(int));
        haveToDeallocate = true;
    }

    if (number == 0) {
        printIntArray(prefix, prefixLength);
        return;
    }
    for (int first = min(number, limit); first > 0; --first) {
        int second = number - first;
        prefix[prefixLength] = first;
        printAllNumberDecompositions(second, first, prefix, prefixLength + 1);
    }

    if (haveToDeallocate)
        free(prefix);
}

int main()
{
    int n = 0;
    promptInt("n: ", &n);
    printAllNumberDecompositions(n, n, NULL, 0);
    return 0;
}
