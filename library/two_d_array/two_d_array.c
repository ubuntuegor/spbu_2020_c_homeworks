#include "two_d_array.h"
#include "../numeric/io.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct TwoDArray {
    int rows;
    int columns;
    int** table;
};

struct TwoDPoint {
    int row;
    int column;
};

TwoDArray* createTwoDArray(int rows, int columns)
{
    TwoDArray* array = (TwoDArray*)malloc(sizeof(TwoDArray));
    array->rows = rows;
    array->columns = columns;
    array->table = (int**)calloc(rows, sizeof(int*));
    for (int i = 0; i < rows; ++i)
        array->table[i] = (int*)calloc(columns, sizeof(int));
    return array;
}

TwoDArray* createTwoDArrayFromConsole()
{
    int rows = 0;
    int columns = 0;
    promptInt("Rows: ", &rows);
    promptInt("Columns: ", &columns);

    TwoDArray* array = createTwoDArray(rows, columns);

    for (int i = 0; i < rows; ++i) {
        printf("Enter row %d: ", i);
        promptIntArray("", array->table[i], columns);
    }

    return array;
}

int getTwoDArrayValue(TwoDArray* array, int row, int column)
{
    if (array == NULL || row >= array->rows || column >= array->columns)
        return 0;
    return array->table[row][column];
}

void setTwoDArrayValue(TwoDArray* array, int row, int column, int value)
{
    if (array == NULL || row >= array->rows || column >= array->columns)
        return;
    array->table[row][column] = value;
}

int getRowMinimum(TwoDArray* array, int row)
{
    if (array == NULL || row >= array->rows)
        return 0;
    int minimum = INT_MAX;
    for (int i = 0; i < array->columns; ++i)
        if (array->table[row][i] < minimum)
            minimum = array->table[row][i];
    return minimum;
}

int getRowMaximum(TwoDArray* array, int row)
{
    if (array == NULL || row >= array->rows)
        return 0;
    int maximum = INT_MIN;
    for (int i = 0; i < array->columns; ++i)
        if (array->table[row][i] > maximum)
            maximum = array->table[row][i];
    return maximum;
}

int getColumnMinimum(TwoDArray* array, int column)
{
    if (array == NULL || column >= array->columns)
        return 0;
    int minimum = INT_MAX;
    for (int i = 0; i < array->rows; ++i)
        if (array->table[i][column] < minimum)
            minimum = array->table[i][column];
    return minimum;
}

int getColumnMaximum(TwoDArray* array, int column)
{
    if (array == NULL || column >= array->columns)
        return 0;
    int maximum = INT_MIN;
    for (int i = 0; i < array->rows; ++i)
        if (array->table[i][column] > maximum)
            maximum = array->table[i][column];
    return maximum;
}

TwoDPoint** getSaddlePoints(TwoDArray* array, int* sizePtr)
{
    if (array == NULL)
        return NULL;
    int* rowMins = (int*)calloc(array->rows, sizeof(int));
    int* columnMaxes = (int*)calloc(array->columns, sizeof(int));

    TwoDPoint** result = (TwoDPoint**)calloc(array->rows > array->columns ? array->rows : array->columns, sizeof(TwoDPoint*));
    int resultCount = 0;

    for (int i = 0; i < array->rows; ++i)
        rowMins[i] = getRowMinimum(array, i);
    for (int i = 0; i < array->columns; ++i)
        columnMaxes[i] = getColumnMaximum(array, i);

    for (int row = 0; row < array->rows; ++row) {
        for (int column = 0; column < array->columns; ++column) {
            if (array->table[row][column] == rowMins[row] && array->table[row][column] == columnMaxes[column])
                result[resultCount] =
        }
    }
}

int getTwoDPointRow(TwoDPoint*);
int getTwoDPointColumn(TwoDPoint*);
void destroyPointArray(TwoDPoint**, int size);

void printTwoDArray(TwoDArray*);

void destroyTwoDArray(TwoDArray** arrayPtr)
{
    if (arrayPtr == NULL || *arrayPtr == NULL)
        return;
    TwoDArray* array = *arrayPtr;

    for (int i = 0; i < array->rows; ++i)
        free(array->table[i]);
    free(array->table);
    free(array);
    *arrayPtr = NULL;
}
