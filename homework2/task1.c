#include "../library/io/integer.h"
#include "../library/numeric/operations.h"
#include <stdio.h>
#include <stdlib.h>

void printAllNumberDecompositions(int number, int limit, int prefix[], int prefixLength)
{
    if (number == 0) {
        printIntArray(prefix, prefixLength);
        return;
    }
    for (int first = min(number, limit); first > 0; first--) {
        int second = number - first;
        prefix[prefixLength] = first;
        printAllNumberDecompositions(second, first, prefix, prefixLength + 1);
    }
}

int main()
{
    int n = 0;
    promptInt("n: ", &n);

    int* prefix = (int*)calloc(n, sizeof(int));
    printAllNumberDecompositions(n, n, prefix, 0);
    free(prefix);
    return 0;
}
