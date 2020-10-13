#pragma once

typedef struct Stack Stack;

Stack* createStack();
int getStackLength(Stack*);
void push(Stack*, double value);
double pop(Stack*);
void destroyStack(Stack**);
