#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int bufferSize = 255;

typedef struct Date {
    int year;
    int month;
    int day;
} Date;

bool isValidDate(char* string)
{
    for (int i = 0; i < 11; ++i) {
        if (string[i] == '\0' && i != 10)
            return false;
        if (i == 2 || i == 5) {
            if (string[i] != '.')
                return false;
        } else if (i == 10) {
            if (string[i] != '\0')
                return false;
        } else {
            if (string[i] < '0' || string[i] > '9')
                return false;
        }
    }
    return true;
}

Date strToDate(char* string)
{
    string[2] = '\0';
    string[5] = '\0';
    int day = atoi(&string[0]);
    int month = atoi(&string[3]);
    int year = atoi(&string[6]);
    string[2] = '.';
    string[5] = '.';
    Date result = { year, month, day };
    return result;
}

Date minDates(Date date1, Date date2)
{
    if (date1.year < date2.year)
        return date1;
    if (date2.year < date1.year)
        return date2;
    if (date1.month < date2.month)
        return date1;
    if (date2.month < date1.month)
        return date2;
    if (date1.day < date2.day)
        return date1;
    if (date2.day < date1.day)
        return date2;
    return date1;
}

void printDate(Date date)
{
    printf("%02d.%02d.%04d\n", date.day, date.month, date.year);
}

int main()
{
    FILE* filePointer = fopen("dates.txt", "r");

    if (filePointer == NULL) {
        printf("Make sure dates.txt is available in the working directory.\n");
        return 0;
    }

    char buffer[bufferSize];
    bool isFirstDateSet = false;
    Date result = { 0, 0, 0 };

    while (!feof(filePointer)) {
        fscanf(filePointer, "%s", buffer);
        if (isValidDate(buffer)) {
            if (isFirstDateSet)
                result = minDates(result, strToDate(buffer));
            else {
                result = strToDate(buffer);
                isFirstDateSet = true;
            }
        }
    }

    if (isFirstDateSet)
        printDate(result);
    else
        printf("No dates found in the text.");

    fclose(filePointer);
    return 0;
}
