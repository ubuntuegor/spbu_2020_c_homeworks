#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

void printVectorDetailed(char* name, Vector* vector)
{
    printf("%s: ", name);
    printVector(vector);
    printf("Length: %f\n", getVectorLength(vector));
}

int main()
{
    int dimensions = 2;
    Vector* vector1 = createVector(dimensions);
    setVectorCoordinate(vector1, 0, 3);
    setVectorCoordinate(vector1, 1, 4);
    Vector* vector2 = createVector(dimensions);
    setVectorCoordinate(vector2, 0, -1);
    setVectorCoordinate(vector2, 1, -1);

    printVectorDetailed("Vector 1", vector1);
    printVectorDetailed("Vector 2", vector2);

    Vector* sum = sumVectors(vector1, vector2);
    printVectorDetailed("Sum", sum);

    Vector* difference = subtractVectors(vector1, vector2);
    printVectorDetailed("Difference", difference);

    printf("Scalar product: %f\n", getScalarProductOfVectors(vector1, vector2));

    destroyVector(&vector1);
    destroyVector(&vector2);
    destroyVector(&sum);
    destroyVector(&difference);

    return 0;
}
