#include "../library/numeric/io.h"
#include "../library/numeric/stack.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int stringLimit = 100;

double performOperationFromStack(Stack* stack, char operation)
{
    double operand2 = pop(stack);
    double operand1 = pop(stack);
    switch (operation) {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        return operand1 / operand2;
    }
}

int main()
{
    int lines = 0;
    promptInt("How many entities are in your postfix expression? ", &lines);

    char inputString[stringLimit];
    memset(inputString, '\0', stringLimit * sizeof(char));

    printf("Please enter your expression (each entity on new line):\n");

    Stack* operandsStack = createStack();

    for (int i = 0; i < lines; i++) {
        scanf("%s", inputString);
        switch (*inputString) {
        case '+':
        case '-':
        case '*':
        case '/':
            if (getStackLength(operandsStack) < 2) {
                printf("Invalid expression.\n");
                destroyStack(&operandsStack);
                return 0;
            }
            double result = performOperationFromStack(operandsStack, *inputString);
            push(operandsStack, result);
            break;
        default:
            push(operandsStack, atof(inputString));
            break;
        }
    }

    if (getStackLength(operandsStack) != 1)
        printf("Invalid expression.\n");
    else
        printf("Result: %f\n", pop(operandsStack));

    destroyStack(&operandsStack);

    return 0;
}
