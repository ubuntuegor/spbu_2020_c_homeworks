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
    int n = 0;
    printf("Number of input numbers: ");
    scanf("%d", &n);

    int* numbers = (int*)calloc(n, sizeof(int));
    printf("Enter numbers:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }

    qsort(numbers, n, sizeof(int), comparison);

    bool success = false;
    int lastNumber = numbers[0];
    for (int i = 1; i < n; i++) {
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
