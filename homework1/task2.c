#include "../library/numeric/operations.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m = 0, n = 0;
    printf("m: ");
    scanf("%d", &m);
    printf("n: ");
    scanf("%d", &n);

    int* numbers = (int*)calloc(n + m + 1, sizeof(*numbers));

    printf("Original array:\n");
    for (int i = 1; i <= m + n; i++) {
        numbers[i] = i;
        printf("%d ", i);
    }
    printf("\n");

    // FIXME: add solution

    printf("Result:\n");
    for (int i = 1; i <= m + n; i++)
        printf("%d ", numbers[i]);
    printf("\n");

    free(numbers);
    return 0;
}
