#include "dfa.h"
#include <stdlib.h>
#include <string.h>

struct DFA {
    DFAState* initialState;
    DFAState* currentState;
};

typedef struct DFATransition {
    enum DFATransitionType type;
    char character;
    DFAState* nextState;
} DFATransition;

struct DFAState {
    bool isFinal;
    bool markedForDestruction;
    int transitionsSize;
    int transitionsAllocated;
    DFATransition** transitions;
};

typedef struct DFAStateDestructionList {
    int size;
    int allocated;
    DFAState** list;
} DFAStateDestructionList;

DFAState DFAFailState = { false, false, 0, 0, NULL };

DFA* createDFA(DFAState* initialState)
{
    if (initialState == NULL)
        return NULL;

    DFA* dfa = (DFA*)malloc(sizeof(DFA));
    dfa->initialState = initialState;
    dfa->currentState = initialState;
    return dfa;
}

DFAState* createDFAState(bool isFinal)
{
    DFAState* dfaState = (DFAState*)malloc(sizeof(DFAState));
    dfaState->isFinal = isFinal;
    dfaState->markedForDestruction = false;
    dfaState->transitionsSize = 0;
    dfaState->transitionsAllocated = 1;
    dfaState->transitions = (DFATransition**)malloc(sizeof(DFATransition*));
    memset(dfaState->transitions, 0, sizeof(DFATransition*));
    return dfaState;
}

DFATransition* createDFATransition(enum DFATransitionType type, char character, DFAState* nextState)
{
    DFATransition* transition = (DFATransition*)malloc(sizeof(DFATransition));
    transition->type = type;
    transition->character = character;
    transition->nextState = nextState;
    return transition;
}

void addTransition(DFAState* fromState, DFAState* toState, enum DFATransitionType type, char character)
{
    if (fromState == NULL || toState == NULL)
        return;

    DFATransition* transition = createDFATransition(type, character, toState);

    if (fromState->transitionsSize == fromState->transitionsAllocated) {
        fromState->transitions = (DFATransition**)realloc(fromState->transitions, sizeof(DFATransition*) * fromState->transitionsAllocated * 2);
        memset(&fromState->transitions[fromState->transitionsAllocated], 0, sizeof(DFATransition*) * fromState->transitionsAllocated);
        fromState->transitionsAllocated *= 2;
    }

    fromState->transitions[fromState->transitionsSize] = transition;
    fromState->transitionsSize++;
}

void moveDFA(DFA* dfa, enum DFATransitionType type, char character)
{
    if (dfa == NULL)
        return;

    DFAState* currentState = dfa->currentState;
    DFAState* nextState = NULL;

    for (int i = 0; i < currentState->transitionsSize && nextState == NULL; ++i) {
        DFATransition* transition = currentState->transitions[i];
        switch (transition->type) {
        case DFADigit:
        case DFALetter:
            if (type == transition->type)
                nextState = transition->nextState;
            break;
        case DFACharacter:
            if (type == transition->type && character == transition->character)
                nextState = transition->nextState;
            break;
        }
    }

    if (nextState == NULL)
        nextState = &DFAFailState;

    dfa->currentState = nextState;
}

bool isInFinalState(DFA* dfa)
{
    return dfa != NULL && dfa->currentState->isFinal;
}

bool destroyDFAState(DFAState** dfaStatePtr)
{
    if (dfaStatePtr == NULL || *dfaStatePtr == NULL)
        return false;

    DFAState* dfaState = *dfaStatePtr;
    for (int i = 0; i < dfaState->transitionsSize; ++i)
        free(dfaState->transitions[i]);
    free(dfaState->transitions);
    free(dfaState);
    *dfaStatePtr = NULL;
    return true;
}

DFAStateDestructionList* createDFAStateDestructionList()
{
    DFAStateDestructionList* destructionList = (DFAStateDestructionList*)malloc(sizeof(DFAStateDestructionList));
    destructionList->size = 0;
    destructionList->allocated = 1;
    destructionList->list = (DFAState**)malloc(sizeof(DFAState*));
    memset(destructionList->list, 0, sizeof(DFAState*));
    return destructionList;
}

void appendToDFAStateDestructionList(DFAStateDestructionList* destructionList, DFAState* state)
{
    if (destructionList == NULL || state == NULL)
        return;

    if (destructionList->size == destructionList->allocated) {
        destructionList->list = (DFAState**)realloc(destructionList->list, sizeof(DFAState*) * destructionList->allocated * 2);
        memset(&destructionList->list[destructionList->allocated], 0, sizeof(DFAState*) * destructionList->allocated);
        destructionList->allocated *= 2;
    }

    destructionList->list[destructionList->size] = state;
    destructionList->size++;
}

void markDFAStateSubtree(DFAState* dfaState, DFAStateDestructionList* destructionList)
{
    if (dfaState == NULL)
        return;

    dfaState->markedForDestruction = true;
    appendToDFAStateDestructionList(destructionList, dfaState);

    for (int i = 0; i < dfaState->transitionsSize; ++i) {
        DFATransition* transition = dfaState->transitions[i];
        if (!transition->nextState->markedForDestruction)
            markDFAStateSubtree(transition->nextState, destructionList);
    }
}

bool destroyDFAStateList(DFAStateDestructionList** destructionListPtr)
{
    if (destructionListPtr == NULL || *destructionListPtr == NULL)
        return false;

    DFAStateDestructionList* destructionList = *destructionListPtr;

    for (int i = 0; i < destructionList->size; ++i)
        destroyDFAState(&destructionList->list[i]);

    free(destructionList->list);
    free(destructionList);
    *destructionListPtr = NULL;
    return true;
}

bool destroyDFA(DFA** dfaPtr)
{
    if (dfaPtr == NULL || *dfaPtr == NULL)
        return false;

    DFA* dfa = *dfaPtr;

    DFAStateDestructionList* destructionList = createDFAStateDestructionList();
    markDFAStateSubtree(dfa->initialState, destructionList);
    destroyDFAStateList(&destructionList);

    free(dfa);
    *dfaPtr = NULL;
    return true;
}
