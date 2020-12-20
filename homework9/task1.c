#include "../library/string/io.h"
#include "parser.h"
#include <stdlib.h>

int main()
{
    printf("Enter expression: ");
    char breakChars[] = { '\n' };
    char* string = readStringUntil(breakChars, sizeof(breakChars));

    if (isValid(string))
        printf("This is a valid expression.\n");
    else
        printf("This is NOT a valid expression.\n");

    free(string);
    return 0;
}
