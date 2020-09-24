#include <stdbool.h>
#include <stdio.h>
#include <string.h>

const int stringLimit = 1000;

int main()
{
    char s1[stringLimit];
    char s2[stringLimit];

    for (int i = 0; i < stringLimit; i++) { // Initialize strings because someone asked for that.
        s1[i] = '\0';
        s2[i] = '\0';
    }

    printf("Haystack: ");
    fgets(s1, stringLimit, stdin);
    printf("Needle: ");
    fgets(s2, stringLimit, stdin);

    int s1Length = strlen(s1) - 1; // "fgets" result includes a newline at the end so we account for that.
    int s2Length = strlen(s2) - 1;
    int searchRegion = s1Length - s2Length + 1;

    int res = 0;

    for (int i = 0; i < searchRegion; i++) {
        bool match = true;

        for (int m = 0; m < s2Length; m++) {
            if (s1[i + m] != s2[m]) {
                match = false;
                break;
            }
        }

        if (match)
            res++;
    }

    printf("Number of occurrences: %d\n", res);
    return 0;
}
