#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
    int x;
    int y;
} Point;

void printSquare(int** numbers, int size, Point* p)
{
    // prints values clockwise starting from top right
    for (int i = 0; i < size - 2; i++) {
        printf("%d\n", numbers[p->x][p->y]);
        p->y++;
    }

    for (int i = 0; i < size - 1; i++) {
        printf("%d\n", numbers[p->x][p->y]);
        p->x--;
    }

    for (int i = 0; i < size - 1; i++) {
        printf("%d\n", numbers[p->x][p->y]);
        p->y--;
    }

    for (int i = 0; i < size; i++) {
        printf("%d\n", numbers[p->x][p->y]);
        p->x++;
    }
}

int main()
{
    int n = 0;

    printf("n: ");
    scanf("%d", &n);

    if (n < 1 || n % 2 == 0) {
        printf("Invalid grid size\n");
        return 1;
    }

    int** numbers = (int**)malloc(n * sizeof(*numbers));
    // initialize grid with consecutive numbers
    for (int i = 0; i < n; i++) {
        numbers[i] = (int*)malloc(n * sizeof(**numbers));
        for (int j = 0; j < n; j++)
            numbers[i][j] = j * n + i + 1;
    }

    int center = (n - 1) / 2;
    Point p = { center, center };
    printf("%d\n", numbers[p.x][p.y]);
    p.x++;
    for (int size = 3; size <= n; size += 2)
        printSquare(numbers, size, &p);

    // free allocated memory
    for (int i = 0; i < n; i++)
        free(numbers[i]);
    free(numbers);
    return 0;
}
