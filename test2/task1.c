#include "../library/numeric/io.h"
#include <stdio.h>

int fibonacci(int n)
{
    if (n <= 0)
        return 0;

    int n1 = 0;
    int n2 = 1;
    int temp = 0;

    for (int i = 0; i < n - 1; ++i) {
        temp = n1 + n2;
        n1 = n2;
        n2 = temp;
    }

    return n2;
}

int main()
{
    int n = 0;
    promptInt("Fibonacci n: ", &n);

    if (n < 0)
        printf("n can't be negative.\n");
    else
        printf("Fibonacci result: %d\n", fibonacci(n));
    return 0;
}
