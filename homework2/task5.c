#include "../library/io/integer.h"
#include <stdio.h>

long long factorialIterative(long long n)
{
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

long long factorialRecursive(long long n)
{
    if (n <= 1)
        return 1;
    return n * factorialRecursive(n - 1);
}

int main()
{
    int n = 0;
    promptInt("n: ", &n);
    printf("Factorial (iterative) %d: %lld\n", n, factorialIterative(n));
    printf("Factorial (recursive) %d: %lld\n", n, factorialRecursive(n));
    return 0;
}
