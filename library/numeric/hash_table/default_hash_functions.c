#include "default_hash_functions.h"
#include <string.h>

int integerHash(long long key, int modulus)
{
    return key < 0 ? -key % modulus : key % modulus;
}

int squareTries(int n, int modulus)
{
    return ((n + 1) * n / 2) % modulus;
}
