#include "../library/dfa/dfa.h"
#include "../library/string/io.h"
#include <stdlib.h>
#include <string.h>

bool isDigit(char character)
{
    return character >= '0' && character <= '9';
}

bool isLetter(char character)
{
    return (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z');
}

DFA* createEmailDFA()
{
    DFAState* state1 = createDFAState(false);
    DFAState* state2 = createDFAState(false);
    DFAState* state3 = createDFAState(false);
    DFAState* state4 = createDFAState(false);
    DFAState* state5 = createDFAState(false);
    DFAState* state6 = createDFAState(true);
    DFAState* state7 = createDFAState(false);

    addTransition(state1, state2, DFALetter, DFAEmptyCharacter);
    addTransition(state1, state2, DFADigit, DFAEmptyCharacter);
    addTransition(state1, state2, DFACharacter, '.');
    addTransition(state1, state2, DFACharacter, '_');
    addTransition(state1, state2, DFACharacter, '%');
    addTransition(state1, state2, DFACharacter, '+');
    addTransition(state1, state2, DFACharacter, '-');

    addTransition(state2, state2, DFALetter, DFAEmptyCharacter);
    addTransition(state2, state2, DFADigit, DFAEmptyCharacter);
    addTransition(state2, state2, DFACharacter, '.');
    addTransition(state2, state2, DFACharacter, '_');
    addTransition(state2, state2, DFACharacter, '%');
    addTransition(state2, state2, DFACharacter, '+');
    addTransition(state2, state2, DFACharacter, '-');

    addTransition(state2, state3, DFACharacter, '@');

    addTransition(state3, state4, DFALetter, DFAEmptyCharacter);
    addTransition(state3, state4, DFADigit, DFAEmptyCharacter);
    addTransition(state3, state4, DFACharacter, '-');

    addTransition(state4, state4, DFALetter, DFAEmptyCharacter);
    addTransition(state4, state4, DFADigit, DFAEmptyCharacter);
    addTransition(state4, state4, DFACharacter, '-');

    addTransition(state4, state5, DFACharacter, '.');

    addTransition(state5, state6, DFALetter, DFAEmptyCharacter);

    addTransition(state5, state7, DFADigit, DFAEmptyCharacter);
    addTransition(state5, state7, DFACharacter, '-');

    addTransition(state6, state6, DFALetter, DFAEmptyCharacter);

    addTransition(state6, state7, DFADigit, DFAEmptyCharacter);
    addTransition(state6, state7, DFACharacter, '-');

    addTransition(state7, state5, DFACharacter, '.');

    addTransition(state7, state7, DFALetter, DFAEmptyCharacter);
    addTransition(state7, state7, DFADigit, DFAEmptyCharacter);
    addTransition(state7, state7, DFACharacter, '-');

    DFA* dfa = createDFA(state1);
    return dfa;
}

int main()
{
    printf("Enter an email: ");

    char breakChars[] = { '\n' };
    char* inputString = readStringUntil(breakChars, sizeof(breakChars));
    int inputStringLength = strlen(inputString) - 1; // Last character is a newline, ignore it.

    DFA* emailDFA = createEmailDFA();

    for (int i = 0; i < inputStringLength; ++i) {
        char character = inputString[i];
        if (isDigit(character))
            moveDFA(emailDFA, DFADigit, DFAEmptyCharacter);
        else if (isLetter(character))
            moveDFA(emailDFA, DFALetter, DFAEmptyCharacter);
        else
            moveDFA(emailDFA, DFACharacter, character);
    }

    if (isInFinalState(emailDFA))
        printf("This is a valid email.\n");
    else
        printf("This is NOT a valid email.\n");

    destroyDFA(&emailDFA);
    free(inputString);
    return 0;
}
