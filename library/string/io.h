#ifndef SPBU_2020_C_STRING_IO_H
#define SPBU_2020_C_STRING_IO_H
#include <stdio.h>

char* readStringUntil(char* breakChars, int breakCharsCount);
char* readWordFromFile(FILE*);

void freeStringArray(char**, int size);

#endif /* SPBU_2020_C_STRING_IO_H */
