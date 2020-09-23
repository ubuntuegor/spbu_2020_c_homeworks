#include "../library/numeric/operations.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("%d\n", max(0, 20));
    printf("%d\n", max(-101010, -74));
    printf("%d\n", max(1, 1));

    printf("%d\n", min(-101010, -74));
    printf("%d\n", min(12, 22));
    printf("%d\n", min(0, 0));

    int a = 10;
    int b = 20;
    printf("%d %d\n", a, b);
    swap(&a, &b);
    printf("%d %d\n", a, b);

    int array[] = { 1, 2, 3 };
    printf("%d %d %d\n", array[0], array[1], array[2]);
    swap(&array[0], &array[2]);
    printf("%d %d %d\n", array[0], array[1], array[2]);
    return 0;
}
