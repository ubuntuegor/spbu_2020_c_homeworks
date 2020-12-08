#include "vector.h"
#include "../library/numeric/io.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Vector {
    int coordinatesCount;
    double* coordinates;
};

Vector* createVector(int coordinatesCount)
{
    Vector* vector = (Vector*)malloc(sizeof(Vector));
    vector->coordinatesCount = coordinatesCount;
    vector->coordinates = (double*)calloc(coordinatesCount, sizeof(double));
    return vector;
}

void setVectorCoordinate(Vector* vector, int coordinate, double value)
{
    if (vector == NULL || coordinate >= vector->coordinatesCount)
        return;
    vector->coordinates[coordinate] = value;
}

double getVectorCoordinate(Vector* vector, int coordinate)
{
    return (vector == NULL || coordinate >= vector->coordinatesCount) ? 0.0 : vector->coordinates[coordinate];
}

double getVectorLength(Vector* vector)
{
    if (vector == NULL)
        return 0.0;
    double squaresSum = 0.0;
    for (int i = 0; i < vector->coordinatesCount; ++i) {
        squaresSum += vector->coordinates[i] * vector->coordinates[i];
    }
    return sqrt(squaresSum);
}

Vector* getNegativeVector(Vector* vector)
{
    if (vector == NULL)
        return NULL;
    Vector* result = createVector(vector->coordinatesCount);
    for (int i = 0; i < vector->coordinatesCount; ++i) {
        result->coordinates[i] = -vector->coordinates[i];
    }
    return result;
}

Vector* sumVectors(Vector* vector1, Vector* vector2)
{
    if (vector1 == NULL || vector2 == NULL || vector1->coordinatesCount != vector2->coordinatesCount)
        return NULL;
    int coordinatesCount = vector1->coordinatesCount;
    Vector* result = createVector(coordinatesCount);
    for (int i = 0; i < coordinatesCount; ++i) {
        result->coordinates[i] = vector1->coordinates[i] + vector2->coordinates[i];
    }
    return result;
}

Vector* subtractVectors(Vector* vector1, Vector* vector2)
{
    if (vector1 == NULL || vector2 == NULL)
        return NULL;
    Vector* negative = getNegativeVector(vector2);
    Vector* result = sumVectors(vector1, negative);
    destroyVector(&negative);
    return result;
}

double getScalarProductOfVectors(Vector* vector1, Vector* vector2)
{
    if (vector1 == NULL || vector2 == NULL || vector1->coordinatesCount != vector2->coordinatesCount)
        return 0.0;
    double result = 0.0;
    for (int i = 0; i < vector1->coordinatesCount; ++i) {
        result += vector1->coordinates[i] * vector2->coordinates[i];
    }
    return result;
}

void printVector(Vector* vector)
{
    printDoubleArray(vector->coordinates, vector->coordinatesCount);
}

void destroyVector(Vector** vectorPtr)
{
    if (vectorPtr == NULL || *vectorPtr == NULL)
        return;
    Vector* vector = *vectorPtr;
    free(vector->coordinates);
    free(vector);
    *vectorPtr = NULL;
}
