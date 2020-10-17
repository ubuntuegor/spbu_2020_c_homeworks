#ifndef SPBU_2020_C_NUMERIC_STACK_H
#define SPBU_2020_C_NUMERIC_STACK_H

typedef struct Stack Stack;

Stack* createStack();
int getStackLength(Stack*);
void push(Stack*, double value);
double pop(Stack*);
void destroyStack(Stack**);

#endif /* SPBU_2020_C_NUMERIC_STACK_H */
