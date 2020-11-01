#include "stack.h"
#include <stdlib.h>

typedef struct StackElement StackElement;

struct Stack {
    StackElement* head;
    int length;
};

struct StackElement {
    double value;
    StackElement* next;
};

Stack* createStack()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->head = NULL;
    stack->length = 0;
    return stack;
}

int getStackLength(Stack* stack)
{
    if (stack == NULL)
        return 0;
    return stack->length;
}

StackElement* createStackElement(double value)
{
    StackElement* element = (StackElement*)malloc(sizeof(StackElement));
    element->value = value;
    element->next = NULL;
    return element;
}

void destroyStackElement(StackElement* element)
{
    free(element);
}

void push(Stack* stack, double value)
{
    if (stack == NULL)
        return;

    StackElement* element = createStackElement(value);
    element->next = stack->head;
    stack->head = element;
    stack->length++;
}

double pop(Stack* stack)
{
    if (stack == NULL || getStackLength(stack) == 0)
        return 0;

    StackElement* poppedElement = stack->head;
    stack->head = poppedElement->next;
    stack->length--;

    double value = poppedElement->value;
    destroyStackElement(poppedElement);
    return value;
}

void destroyStack(Stack** stackPtr)
{
    if (stackPtr == NULL || *stackPtr == NULL)
        return;

    while (getStackLength(*stackPtr) > 0)
        pop(*stackPtr);

    free(*stackPtr);
    *stackPtr = NULL;
}
