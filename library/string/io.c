#include "io.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readStringUntil(char* breakChars, int breakCharsCount)
{
    int allocatedBytes = 2;
    char* string = (char*)malloc(allocatedBytes);
    memset(string, '\0', allocatedBytes);

    bool finishedReading = false;
    int writePointer = 0;

    while (!finishedReading) {
        if (writePointer >= allocatedBytes - 1) { // Always have a spare byte in case we need to terminate the string.
            allocatedBytes *= 2;
            string = (char*)realloc(string, allocatedBytes);
        }

        char readCharacter = '\0';
        scanf("%c", &readCharacter);
        string[writePointer] = readCharacter;
        writePointer++;

        for (int i = 0; i < breakCharsCount; i++) {
            if (readCharacter == breakChars[i]) {
                finishedReading = true;
                string[writePointer] = '\0';
            }
        }
    }

    return string;
}
