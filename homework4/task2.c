#include "../library/numeric/io.h"
#include <stdio.h>

void convertLEToBE(unsigned char* result, unsigned char* number, int bytesCount)
{
    for (int i = 0; i < bytesCount; i++) {
        result[i] = number[bytesCount - 1 - i];
    }
}

short getExponent(unsigned char* bytes)
{
    unsigned short shifted = bytes[0] & (~0x80);
    shifted <<= 4;
    shifted += bytes[1] >> 4;
    return shifted - 1023;
}

unsigned long long getFraction(char* bytes)
{
    unsigned long long result = 0;
    for (int i = 1; i < 8; i++) {
        result += bytes[i];
        result <<= 8;
    }
    result <<= 4;
    return result;
}

int getFractionLength(unsigned long long fraction)
{
    int length = 0;
    while (fraction != 0) {
        fraction <<= 1;
        length++;
    }
    return length;
}

int main()
{
    double number = 0;
    promptDouble("Enter a number: ", &number);

    unsigned char* pointer = (unsigned char*)(&number);
    unsigned char bytes[8] = { 0 };

    convertLEToBE(bytes, pointer, 8);

    unsigned char signBit = (bytes[0] >> 7);
    short exponent = getExponent(bytes);
    unsigned long long fraction = getFraction(bytes);

    if (exponent == -1023 && fraction == 0) {
        printf("This is a zero\n");
        return 0;
    }

    unsigned long long fractionLength = getFractionLength(fraction);

    fraction >>= 64 - fractionLength;
    unsigned long long divider = 1;
    divider <<= fractionLength;

    char sign = (signBit) ? '-' : '+';
    double m = (double)fraction / divider + 1;

    printf("Result: %c%f*2^(%d)\n", sign, m, exponent);

    return 0;
}
