#include <stdio.h>

int factorial(int n)
{
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int factorialRecursive(int n)
{
    if (n <= 1)
        return 1;
    return n * factorialRecursive(n - 1);
}

int main()
{
    printf("Factorial 5: %d\n", factorial(5));
    printf("Factorial (recursive) 5: %d\n", factorialRecursive(5));
    return 0;
}
