#include "../library/numeric/io.h"
#include <stdio.h>

short getExponent(unsigned long long bits)
{
    unsigned long long mask = 0x7ff0000000000000;
    unsigned short shifted = (bits & mask) >> 52;
    return shifted - 1023;
}

unsigned long long getFraction(unsigned long long bits)
{
    unsigned long long mask = 0x000fffffffffffff;
    return (bits & mask);
}

int main()
{
    double number = 0;
    promptDouble("Enter a number: ", &number);

    unsigned long long bits = *(unsigned long long*)&number;

    unsigned char signBit = (bits >> 63);
    short exponent = getExponent(bits);
    unsigned long long fraction = getFraction(bits);

    if (exponent == -1023 && fraction == 0) {
        printf("This is a zero\n");
        return 0;
    }

    unsigned long long divider = (unsigned long long)1 << 52;

    char sign = (signBit) ? '-' : '+';
    double m = (double)fraction / divider + 1;

    printf("Result: %c%f*2^(%d)\n", sign, m, exponent);

    return 0;
}
