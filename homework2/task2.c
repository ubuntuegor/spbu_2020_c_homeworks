#include "../library/numeric/io.h"
#include "../library/numeric/operations.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void askForGameRules(int* digitCount)
{
    bool correctInput = false;
    while (!correctInput) {
        promptInt("\nHow many digits should there be in my number? (4 to 10): ", digitCount);

        if (*digitCount >= 4 && *digitCount <= 10)
            correctInput = true;
        else
            printf("Please choose another number.\n");
    }
}

void generateGameNumber(int result[], int length)
{
    int i = 0;
    bool* usedDigits = (bool*)calloc(10, sizeof(bool));
    while (i < length) {
        int generated = rand() % 10;
        if (!usedDigits[generated]) {
            result[i] = generated;
            usedDigits[generated] = true;
            ++i;
        }
    }
    free(usedDigits);
}

bool checkUnique(int digits[], int length)
{
    bool* usedDigits = (bool*)calloc(10, sizeof(bool));
    for (int i = 0; i < length; ++i) {
        int digit = digits[i];
        if (usedDigits[digit]) {
            free(usedDigits);
            return false;
        }
        usedDigits[digit] = true;
    }
    free(usedDigits);
    return true;
}

void countBullsAndCows(int correctDigits[], int guessedDigits[], int digitCount, int* bulls, int* cows)
{
    for (int i = 0; i < digitCount; ++i) {
        bool foundPair = false;
        for (int j = 0; j < digitCount && !foundPair; ++j) {
            if (guessedDigits[i] == correctDigits[j]) {
                if (i == j)
                    ++(*bulls);
                else
                    ++(*cows);
                foundPair = true;
            }
        }
    }
}

int main()
{
    printf("Bulls and Cows\n\nI'm thinking of a number... Try to guess it and I will tell you "
           "how many digits of your number are in the right position (bulls) or wrong position "
           "(cows).\nGood luck!\n");
    srand(time(NULL)); // Set random seed to current time.

    int digitCount = 0;
    askForGameRules(&digitCount);

    int* correctDigits = (int*)calloc(digitCount, sizeof(int));
    generateGameNumber(correctDigits, digitCount);

    bool guessed = false;
    while (!guessed) {
        unsigned long long guess = 0;
        promptLLU("\nYour guess: ", &guess);

        if (guess < 0) {
            printf("Negative number? Seriously? Read the game rules once again.\n");
            continue;
        }

        int guessDigitCount = countDigits(guess);
        if (guessDigitCount > digitCount) {
            printf("Your number is too large!\n");
            continue;
        }

        int* guessDigits = (int*)calloc(digitCount, sizeof(int));
        dissectNumberToDigits(guessDigits, digitCount, guess);

        if (!checkUnique(guessDigits, digitCount)) {
            printf("Your number shouldn't contain repeating digits!\n");
            free(guessDigits);
            continue;
        }

        int bulls = 0;
        int cows = 0;

        countBullsAndCows(correctDigits, guessDigits, digitCount, &bulls, &cows);

        if (bulls == digitCount)
            guessed = true;
        else
            printf("%d bulls, %d cows\n", bulls, cows);

        free(guessDigits);
    }

    printf("You guessed it! Congratulations!\n");
    free(correctDigits);

    return 0;
}
