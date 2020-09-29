#include "../library/numeric/operations.h"
#include <stdio.h>
#include <stdlib.h>

void printArray(int array[], int arrayLength)
{
    for (int i = 0; i < arrayLength; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void solve(int number, int limit, int prefix[], int prefixLength)
{
    if (number == 0) {
        printArray(prefix, prefixLength);
        return;
    }
    for (int first = min(number, limit); first > 0; first--) {
        int second = number - first;
        prefix[prefixLength] = first;
        solve(second, first, prefix, prefixLength + 1);
    }
}

int main()
{
    int n = 0;
    printf("n: ");
    scanf("%d", &n);

    int* prefix = (int*)calloc(n, sizeof(int));
    solve(n, n, prefix, 0);
    free(prefix);
    return 0;
}
