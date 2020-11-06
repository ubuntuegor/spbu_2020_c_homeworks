#include "../library/numeric/io.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool mergeSortDesc(int result[], int stack1[], int stack1Count, int stack2[], int stack2Count)
{
    int index1 = 0;
    int index2 = 0;
    int lastValue = INT_MAX;

    while (index1 + index2 < stack1Count + stack2Count) {
        int weight1 = (index1 < stack1Count) ? stack1[index1] : INT_MIN;
        int weight2 = (index2 < stack2Count) ? stack2[index2] : INT_MIN;

        if (weight1 > lastValue || weight2 > lastValue)
            return false;

        if (weight1 > weight2) {
            result[index1 + index2] = weight1;
            lastValue = result[index1 + index2];
            index1++;
        } else {
            result[index1 + index2] = weight2;
            lastValue = result[index1 + index2];
            index2++;
        }
    }
    return true;
}

int main()
{
    int stack1Count = 0;
    promptInt("How many notebooks does Vasya have? ", &stack1Count);
    int* stack1 = (int*)calloc(stack1Count, sizeof(int));
    promptIntArray("Enter descending subject weights:\n", stack1, stack1Count);

    int stack2Count = 0;
    promptInt("How many notebooks does Petya have? ", &stack2Count);
    int* stack2 = (int*)calloc(stack2Count, sizeof(int));
    promptIntArray("Enter descending subject weights:\n", stack2, stack2Count);

    int combinedCount = stack1Count + stack2Count;

    int* combined = (int*)calloc(combinedCount, sizeof(int));
    bool mergeResult = mergeSortDesc(combined, stack1, stack1Count, stack2, stack2Count);

    if (!mergeResult) {
        printf("Make sure your books are properly sorted.\n");
        return 0;
    }

    printf("Your books: ");
    printIntArray(combined, combinedCount);

    free(stack1);
    free(stack2);
    free(combined);

    return 0;
}
