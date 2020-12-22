#ifndef SPBU_2020_C_VECTOR_H
#define SPBU_2020_C_VECTOR_H

typedef struct Vector Vector;

Vector* createVector(int coordinatesCount);
void setVectorCoordinate(Vector*, int coordinate, double value);
double getVectorCoordinate(Vector*, int coordinate);
double getVectorLength(Vector*);
Vector* getNegativeVector(Vector*);
Vector* sumVectors(Vector* vector1, Vector* vector2);
Vector* subtractVectors(Vector* vector1, Vector* vector2);
double getScalarProductOfVectors(Vector* vector1, Vector* vector2);
void printVector(Vector*);
void destroyVector(Vector**);

#endif /* SPBU_2020_C_VECTOR_H */
