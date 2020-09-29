#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 0;
    printf("Number of input numbers: ");
    scanf("%d", &n);

    int* numbers = (int*)calloc(n, sizeof(int));
    printf("Enter numbers:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &numbers[i]);

    int i = 0;
    int p = 0;

    while (i < n) {
        while (p < n && numbers[p] == 0)
            p++;
        if (p < n)
            numbers[i] = numbers[p];
        else
            numbers[i] = 0;
        i++;
        p++;
    }

    printf("Result: ");
    for (int i = 0; i < n; i++)
        printf("%d ", numbers[i]);
    printf("\n");

    free(numbers);

    return 0;
}
