#include "parser.h"
#include "../library/dfa/realNumberDFA.h"
#include <string.h>

void skipWhitespace(char* string, int size, int* pointer);
bool id(char* string, int size, int* pointer);
bool multiply(char* string, int size, int* pointer);
bool multiplyMark(char* string, int size, int* pointer);
bool sum(char* string, int size, int* pointer);
bool sumMark(char* string, int size, int* pointer);
bool subtract(char* string, int size, int* pointer);
bool subtractMark(char* string, int size, int* pointer);
bool division(char* string, int size, int* pointer);
bool divisionMark(char* string, int size, int* pointer);

void skipWhitespace(char* string, int size, int* pointer)
{
    while (*pointer < size && (string[*pointer] == ' ' || string[*pointer] == '\n')) {
        (*pointer)++;
    }
}

bool division(char* string, int size, int* pointer)
{
    return subtract(string, size, pointer) && divisionMark(string, size, pointer);
}

bool divisionMark(char* string, int size, int* pointer)
{
    if (*pointer >= size)
        return true;
    if (string[*pointer] == '/') {
        (*pointer)++;
        skipWhitespace(string, size, pointer);
        return division(string, size, pointer);
    } else {
        return true;
    }
}

bool subtract(char* string, int size, int* pointer)
{
    return sum(string, size, pointer) && subtractMark(string, size, pointer);
}

bool subtractMark(char* string, int size, int* pointer)
{
    if (*pointer >= size)
        return true;
    if (string[*pointer] == '-') {
        (*pointer)++;
        skipWhitespace(string, size, pointer);
        return subtract(string, size, pointer);
    } else {
        return true;
    }
}

bool sum(char* string, int size, int* pointer)
{
    return multiply(string, size, pointer) && sumMark(string, size, pointer);
}

bool sumMark(char* string, int size, int* pointer)
{
    if (*pointer >= size)
        return true;
    if (string[*pointer] == '+') {
        (*pointer)++;
        skipWhitespace(string, size, pointer);
        return sum(string, size, pointer);
    } else {
        return true;
    }
}

bool multiply(char* string, int size, int* pointer)
{
    return id(string, size, pointer) && multiplyMark(string, size, pointer);
}

bool multiplyMark(char* string, int size, int* pointer)
{
    if (*pointer >= size)
        return true;
    if (string[*pointer] == '*') {
        (*pointer)++;
        skipWhitespace(string, size, pointer);
        return multiply(string, size, pointer);
    } else {
        return true;
    }
}

bool id(char* string, int size, int* pointer)
{
    if (*pointer >= size)
        return false;
    int startPointer = *pointer;

    DFA* realNumberDFA = createRealNumberDFA();
    while (*pointer < size && string[*pointer] != ' ' && string[*pointer] != '\n') {
        char character = string[*pointer];
        if (isDigit(character))
            moveDFA(realNumberDFA, DFADigit, DFAEmptyCharacter);
        else
            moveDFA(realNumberDFA, DFACharacter, character);
        (*pointer)++;
    }

    bool result = false;
    if (isInFinalState(realNumberDFA))
        result = true;
    else
        *pointer = startPointer;

    destroyDFA(&realNumberDFA);

    skipWhitespace(string, size, pointer);
    return result;
}

bool isValid(char* string)
{
    int stringLength = strlen(string);
    int pointer = 0;
    return division(string, stringLength, &pointer) && pointer == stringLength;
}
