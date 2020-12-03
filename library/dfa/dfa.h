#ifndef SPBU_2020_C_DFA_H
#define SPBU_2020_C_DFA_H
#include <stdbool.h>

typedef struct DFA DFA;
typedef struct DFAState DFAState;
enum DFATransitionType { DFADigit,
    DFALetter,
    DFACharacter };

#define DFAEmptyCharacter 0

DFAState* createDFAState(bool isFinal);
void addTransition(DFAState* fromState, DFAState* toState, enum DFATransitionType, char character);
bool destroyDFAState(DFAState**);

DFA* createDFA(DFAState* initialState);
void moveDFA(DFA*, enum DFATransitionType, char character);
bool isInFinalState(DFA*);
bool destroyDFA(DFA**);

#endif /* SPBU_2020_C_DFA_H */
