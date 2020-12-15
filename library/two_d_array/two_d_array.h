#ifndef SPBU_2020_C_TWO_D_ARRAY_H
#define SPBU_2020_C_TWO_D_ARRAY_H

typedef struct TwoDArray TwoDArray;
typedef struct TwoDPoint TwoDPoint;

TwoDArray* createTwoDArray(int rows, int columns);
TwoDArray* createTwoDArrayFromConsole();

int getTwoDArrayValue(TwoDArray*, int row, int column);
void setTwoDArrayValue(TwoDArray*, int row, int column, int value);

int getRowMinimum(TwoDArray*, int row);
int getRowMaximum(TwoDArray*, int row);
int getColumnMinimum(TwoDArray*, int column);
int getColumnMaximum(TwoDArray*, int column);

TwoDPoint** getSaddlePoints(TwoDArray*, int* sizePtr);
int getTwoDPointRow(TwoDPoint*);
int getTwoDPointColumn(TwoDPoint*);
void destroyPointArray(TwoDPoint**, int size);

void printTwoDArray(TwoDArray*);

void destroyTwoDArray(TwoDArray**);

#endif /* SPBU_2020_C_TWO_D_ARRAY_H */
