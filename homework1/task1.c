#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
    int x;
    int y;
} Point;

void printSquare(int **numbers, int size, Point *p)
{
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
    int n = 5;

    int **numbers;
    numbers = malloc(n * sizeof(*numbers));

    for (int i = 0; i < n; i++) {
        numbers[i] = malloc(n * sizeof(**numbers));
        for (int j = 0; j < n; j++)
            numbers[i][j] = j * n + i + 1;
    }

    int center = (n - 1) / 2;
    Point p = {center, center};

    printf("%d\n", numbers[p.x][p.y]);

    p.x++;
    int size = 3;
    while (size <= n) {
        printSquare(numbers, size, &p);
        size += 2;
    }

    return 0;
}
