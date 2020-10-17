#include "../library/numeric/io.h"
#include <stdbool.h>
#include <stdio.h>

void getIntBinaryRepresentation(bool bitArray[], int number)
{
    for (int i = 0; i < sizeof(int) * 8; ++i) {
        bitArray[i] = number & 1;
        number >>= 1;
    }
}

void printBitArray(char prefix[], bool bitArray[])
{
    printf("%s", prefix);
    for (int i = sizeof(int) * 8 - 1; i >= 0; --i) {
        printf("%u", bitArray[i]);
    }
    printf("\n");
}

void sumBitArrays(bool sum[], bool number1[], bool number2[])
{
    bool movedDigit = 0;
    for (int i = 0; i < sizeof(int) * 8; ++i) {
        int digitSum = number1[i] + number2[i] + movedDigit;
        sum[i] = digitSum & 1;
        movedDigit = digitSum >> 1;
    }
}

int getBitArrayAsInt(bool bitArray[])
{
    int result = 0;
    for (int i = sizeof(int) * 8 - 1; i > 0; --i) {
        result += bitArray[i];
        result <<= 1;
    }
    result += bitArray[0];
    return result;
}

int main()
{
    int number1 = 0;
    int number2 = 0;
    promptInt("Enter first number: ", &number1);
    promptInt("Enter second number: ", &number2);

    bool binaryNumber1[sizeof(int) * 8] = { 0 };
    bool binaryNumber2[sizeof(int) * 8] = { 0 };
    getIntBinaryRepresentation(binaryNumber1, number1);
    getIntBinaryRepresentation(binaryNumber2, number2);

    printBitArray("First number in binary: ", binaryNumber1);
    printBitArray("Second number in binary: ", binaryNumber2);

    bool binarySum[sizeof(int) * 8] = { 0 };
    sumBitArrays(binarySum, binaryNumber1, binaryNumber2);
    int sumAsInt = getBitArrayAsInt(binarySum);

    if (sumAsInt != number1 + number2) {
        printf("Something went wrong...");
        return 1;
    }

    printBitArray("Their sum in binary: ", binarySum);
    printf("Their sum in decimal: %d\n", sumAsInt);

    return 0;
}
