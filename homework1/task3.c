#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char s1[] = "ahahaha";
    char s2[] = "aha";

    int s1Length = strlen(s1);
    int s2Length = strlen(s2);
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
