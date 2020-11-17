#ifndef SPBU_2020_C_STRING_IO_H
#define SPBU_2020_C_STRING_IO_H
#include <stdio.h>

char* readStringUntil(char* breakChars, int breakCharsCount);
char* readWordFromFile(FILE*);

char** initializeStringArray(char* firstValue);
char** appendToStringArray(char**, int currentLength, char* newValue);
void freeStringArray(char**, int size);

#endif /* SPBU_2020_C_STRING_IO_H */
