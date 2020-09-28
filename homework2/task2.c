#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateNumber(int* result, int length)
{
    int i = 0;
    while (i < length) {
        result[i] = rand() / (double)RAND_MAX * 10;
        if (result[i] == 10)
            result[i]--;
        bool unique = true;
        for (int j = 0; j < i; j++) {
            if (result[j] == result[i]) {
                unique = false;
                break;
            }
        }
        if (unique)
            i++;
    }
}

bool checkUnique(int* digits, int length)
{
    bool result = true;
    for (int i = 1; i < length; i++) {
        for (int j = 0; j < i; j++) {
            if (digits[i] == digits[j]) {
                result = false;
                break;
            }
        }
        if (!result)
            break;
    }
    return result;
}

void dissectNumberToDigits(int* result, int number)
{
    result[0] = number / 1000;
    result[1] = (number - result[0] * 1000) / 100;
    result[2] = (number - result[0] * 1000 - result[1] * 100) / 10;
    result[3] = number % 10;
}

int main()
{
    printf("Bulls and Cows\n\nI'm thinking of a 4-digit number... Try to guess it and I will "
           "tell you how many digits of your number are in the right position (bulls) or "
           "wrong position (cows).\nGood luck!\n");
    srand(time(NULL));

    int correctDigits[4] = { 0, 0, 0, 0 };
    generateNumber(correctDigits, 4);
    // printf("[DEBUG] %d%d%d%d\n", correctDigits[0], correctDigits[1], correctDigits[2], correctDigits[3]);

    while (1) {
        int guess = 0;
        printf("\nGuess: ");
        scanf("%d", &guess);

        int guessDigits[4] = { 0, 0, 0, 0 };
        dissectNumberToDigits(guessDigits, guess);

        if (guess > 9999) {
            printf("Your number is too large!\n");
            continue;
        }

        if (!checkUnique(guessDigits, 4)) {
            printf("Your number shouldn't contain repeating digits!\n");
            continue;
        }

        int bulls = 0;
        int cows = 0;

        // Check bulls
        for (int i = 0; i < 4; i++)
            if (guessDigits[i] == correctDigits[i])
                bulls++;

        if (bulls == 4) {
            printf("You guessed it! Congratulations!\n");
            break;
        }

        // Check cows
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == j)
                    continue;
                if (guessDigits[i] == correctDigits[j]) {
                    cows++;
                    break;
                }
            }
        }

        printf("%d bulls, %d cows\n", bulls, cows);
    }

    return 0;
}
