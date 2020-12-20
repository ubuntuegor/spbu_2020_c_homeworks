#include "../library/dfa/realNumberDFA.h"
#include "../library/string/io.h"
#include <stdlib.h>
#include <string.h>

int main()
{
    printf("Enter a real number: ");

    char breakChars[] = { '\n' };
    char* inputString = readStringUntil(breakChars, sizeof(breakChars));
    int inputStringLength = strlen(inputString) - 1; // Last character is a newline, ignore it.

    DFA* realNumberDFA = createRealNumberDFA();

    for (int i = 0; i < inputStringLength; ++i) {
        char character = inputString[i];
        if (isDigit(character))
            moveDFA(realNumberDFA, DFADigit, DFAEmptyCharacter);
        else
            moveDFA(realNumberDFA, DFACharacter, character);
    }

    if (isInFinalState(realNumberDFA))
        printf("That's a valid real number.\n");
    else
        printf("Entered string is not a real number.\n");

    destroyDFA(&realNumberDFA);
    free(inputString);
    return 0;
}
