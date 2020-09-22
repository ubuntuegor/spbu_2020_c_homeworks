#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char s1[100];
    char s2[100];

    printf("haystack: ");
    fgets(s1, 100, stdin);
    printf("needle: ");
    fgets(s2, 100, stdin);

    int s1Length = strlen(s1) - 1; // fgets includes newline at the end of the string
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

    printf("%d\n", res);
    return 0;
}
