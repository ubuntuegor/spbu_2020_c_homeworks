#include "../library/numeric/stack.h"
#include "../library/string/io.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isOperator(char character)
{
    return (character == '+') || (character == '-') || (character == '*') || (character == '/');
}

double calculateOperationFromStack(Stack* stack, char operation)
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
    Stack* numbers = createStack();

    char breakChars[] = { ' ', '\n' };
    bool finishedInput = false;
    bool invalidExpression = false;

    printf("Enter your postfix expression: ");

    while (!finishedInput) {
        char* input = readStringUntil(breakChars, sizeof(breakChars));

        if (isOperator(input[0])) {
            if (getStackLength(numbers) < 2) {
                invalidExpression = true;
                break;
            }
            double result = calculateOperationFromStack(numbers, input[0]);
            push(numbers, result);
        } else {
            double inputNumber = atof(input);
            push(numbers, inputNumber);
        }

        if (input[strlen(input) - 1] == '\n')
            finishedInput = true;

        free(input);
    }

    if (!invalidExpression && getStackLength(numbers) == 1)
        printf("Result: %f\n", pop(numbers));
    else
        printf("Invalid expression\n");

    destroyStack(&numbers);

    return 0;
}
