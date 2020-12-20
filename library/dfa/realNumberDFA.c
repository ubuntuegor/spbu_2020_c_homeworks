#include "realNumberDFA.h"
#include <stdlib.h>

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
