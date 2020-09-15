#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// odd = 2n + 1

int main()
{
    int n = 100;

    int oddCount = (n + 1) / 2;
    bool* notPrimeOdds = calloc(oddCount, sizeof(bool));

    for (int n1 = 1; (4 * n1 * n1 + 4 * n1 + 1) <= n; n1++) { // (2n+1)^2
        for (int n2 = n1;; n2++) {
            int odd1 = 2 * n1 + 1;
            int odd2 = 2 * n2 + 1;
            int multiplication = odd1 * odd2;

            if (multiplication > n) {
                break;
            } else {
                int multiplicationToN = (multiplication - 1) / 2;
                notPrimeOdds[multiplicationToN] = true;
            }
        }
    }

    if (n > 2)
        printf("2\n");

    for (int i = 1; i < oddCount; i++)
        printf(notPrimeOdds[i] ? "" : "%d\n", 2 * i + 1);

    return 0;
}
