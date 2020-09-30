#include "../library/numeric/io.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 0;
    promptInt("Number of input numbers: ", &n);

    int* numbers = (int*)calloc(n, sizeof(int));
    promptIntArray("Enter numbers:\n", numbers, n);

    int i = 0;
    int p = 0;
    while (i < n) {
        while (p < n && numbers[p] == 0) {
            ++p;
        }
        numbers[i] = (p < n) ? numbers[p] : 0;
        ++i;
        ++p;
    }

    printf("Result: ");
    printIntArray(numbers, n);
    free(numbers);

    return 0;
}
