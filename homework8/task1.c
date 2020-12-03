#include "../library/dfa/dfa.h"
#include "../library/string/io.h"
#include <stdlib.h>
#include <string.h>

bool isDigit(char character)
{
    return character >= '0' && character <= '9';
}

DFAState* createNumberModel(bool isFinal)
{
    DFAState* state = createDFAState(isFinal);
    addTransition(state, state, DFADigit, DFAEmptyCharacter);
    return state;
}

DFAState* createSignedNumberModel(bool isFinal, DFAState** digitStatePtr)
{
    DFAState* initialState = createDFAState(false);
    DFAState* signState = createDFAState(false);
    DFAState* digitState = createNumberModel(isFinal);

    addTransition(initialState, signState, DFACharacter, '+');
    addTransition(initialState, signState, DFACharacter, '-');
    addTransition(initialState, digitState, DFADigit, DFAEmptyCharacter);
    addTransition(signState, digitState, DFADigit, DFAEmptyCharacter);

    if (digitStatePtr != NULL)
        *digitStatePtr = digitState;
    return initialState;
}

DFA* createRealNumberDFA()
{
    DFAState* exponent = createSignedNumberModel(true, NULL);
    DFAState* dotState = createDFAState(false);
    DFAState* fractionState = createNumberModel(true);
    DFAState* wholeNumberState = NULL;
    DFAState* initialState = createSignedNumberModel(true, &wholeNumberState);

    addTransition(wholeNumberState, exponent, DFACharacter, 'E');
    addTransition(wholeNumberState, dotState, DFACharacter, '.');
    addTransition(dotState, fractionState, DFADigit, DFAEmptyCharacter);
    addTransition(fractionState, exponent, DFACharacter, 'E');

    DFA* dfa = createDFA(initialState);
    return dfa;
}

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
