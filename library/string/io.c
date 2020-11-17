#include "io.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isLetter(char letter)
{
    return letter >= 'a' && letter <= 'z';
}

char* readStringUntil(char* breakChars, int breakCharsCount)
{
    int allocatedBytes = 2;
    char* string = (char*)malloc(allocatedBytes);
    memset(string, 0, allocatedBytes);

    bool finishedReading = false;
    int writePointer = 0;

    while (!finishedReading) {
        if (writePointer >= allocatedBytes - 1) { // Always have a spare byte in case we need to terminate the string.
            int halfBytes = allocatedBytes;
            allocatedBytes *= 2;
            string = (char*)realloc(string, allocatedBytes);
            memset(string + halfBytes, 0, halfBytes);
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

char* readWordFromFile(FILE* filePtr)
{
    if (filePtr == NULL)
        return NULL;

    char* string = NULL;
    int allocatedBytes = 0;
    int writeIndex = 0;

    bool finishedReading = false;

    while (!finishedReading) {
        char readCharacter = fgetc(filePtr);

        if (readCharacter == EOF) {
            finishedReading = true;
            break;
        }

        readCharacter = tolower(readCharacter);

        if (isLetter(readCharacter)) {
            if (string == NULL) {
                allocatedBytes = 2;
                string = (char*)calloc(allocatedBytes, sizeof(char));
            } else if (writeIndex >= allocatedBytes - 1) {
                int halfBytes = allocatedBytes;
                allocatedBytes *= 2;
                string = (char*)realloc(string, allocatedBytes);
                memset(string + halfBytes, 0, halfBytes);
            }

            string[writeIndex] = readCharacter;
            writeIndex++;
        } else if (string != NULL) {
            string[writeIndex] = '\0';
            finishedReading = true;
        }
    }

    return string;
}

char** initializeStringArray(char* firstValue)
{
    if (firstValue == NULL)
        return NULL;

    char** stringArray = (char**)calloc(1, sizeof(char*));
    stringArray[0] = (char*)calloc(strlen(firstValue) + 1, sizeof(char));
    strcpy(stringArray[0], firstValue);
    return stringArray;
}

char** appendToStringArray(char** stringArray, int currentLength, char* newValue)
{
    if (stringArray == NULL || newValue == NULL)
        return NULL;

    int newLength = currentLength + 1;
    stringArray = (char**)realloc(stringArray, newLength * sizeof(char*));
    stringArray[currentLength] = (char*)calloc(strlen(newValue) + 1, sizeof(char));
    strcpy(stringArray[currentLength], newValue);
    return stringArray;
}

void freeStringArray(char** stringArray, int size)
{
    if (stringArray == NULL)
        return;
    for (int i = 0; i < size; ++i)
        free(stringArray[i]);
    free(stringArray);
}
