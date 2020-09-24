#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
    int x;
    int y;
} Point;

void printGrid(int** numbers, int size)
{
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++)
            printf("%d\t", numbers[x][y]);
        printf("\n");
    }
}

void printEdge(int** numbers, int size, Point* p)
{
    // prints values clockwise starting from top right
    for (int i = 0; i < size - 2; i++) {
        printf("%d ", numbers[p->x][p->y]);
        p->y++;
    }

    for (int i = 0; i < size - 1; i++) {
        printf("%d ", numbers[p->x][p->y]);
        p->x--;
    }

    for (int i = 0; i < size - 1; i++) {
        printf("%d ", numbers[p->x][p->y]);
        p->y--;
    }

    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[p->x][p->y]);
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
    for (int x = 0; x < n; x++) {
        numbers[x] = (int*)malloc(n * sizeof(**numbers));
        for (int y = 0; y < n; y++)
            numbers[x][y] = y * n + x + 1;
    }

    printf("\nSource array:\n");
    printGrid(numbers, n);

    printf("\nOutput spiral:\n");
    int center = (n - 1) / 2;
    Point p = { center, center };
    printf("%d ", numbers[p.x][p.y]);
    p.x++;
    for (int size = 3; size <= n; size += 2)
        printEdge(numbers, size, &p);
    printf("\n");

    // free allocated memory
    for (int i = 0; i < n; i++)
        free(numbers[i]);
    free(numbers);
    return 0;
}
