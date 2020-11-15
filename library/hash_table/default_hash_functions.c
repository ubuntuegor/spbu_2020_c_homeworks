#include "default_hash_functions.h"
#include "../numeric/operations.h"
#include <string.h>

int rollingHashPrime2(char* key, int modulus)
{
    if (key == NULL)
        return 0;
    int characterCount = strlen(key);
    int n = characterCount - 1;

    int result = 0;

    for (int i = 0; i < characterCount; i++) {
        result += key[i] * binpow(2, n - i) % modulus;
        result %= modulus;
    }

    return result;
}

int squareTries(int n, int modulus)
{
    double a = n + 1;
    double b = (double)n / 2;
    return (int)(a * b) % modulus;
}
