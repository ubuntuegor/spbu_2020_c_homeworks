#include <stdio.h>
#include <stdlib.h>

void swap(int* numbers, int a, int b)
{
    int temp = numbers[a];
    numbers[a] = numbers[b];
    numbers[b] = temp;
}

void swapMany(int* numbers, int a, int b, int count)
{
    for (int i = 0; i < count; i++)
        swap(numbers, a + i, b + i);
}

void solve(int* numbers, int m, int n)
{
    if (m > n) {
        swapMany(numbers, m + 1, m + 1 - n, n);
        solve(numbers, m - n, n);
    } else if (m < n) {
        swapMany(numbers, 1, n + 1, m);
        solve(numbers, m, n - m);
    } else
        swapMany(numbers, 1, m + 1, m);
}

int main()
{
    int m = 4;
    int n = 7;

    int* numbers;
    numbers = calloc(n + m + 1, sizeof(*numbers));

    for (int i = 1; i <= n + m; i++) {
        numbers[i] = i;
        printf("%d ", i);
    }
    printf("\n");

    solve(numbers, m, n);

    for (int i = 1; i <= n + m; i++)
        printf("%d ", numbers[i]);

    return 0;
}
