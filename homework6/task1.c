#include "../library/hash_table/hash_table.h"
#include "../library/string/io.h"
#include <stdio.h>
#include <stdlib.h>

const char inputFilename[] = "hw6task1_input.txt";
const int topWordsAmount = 10;

int compareHashElementsDesc(const void* a, const void* b)
{
    return getHashElementValue(*(HashElement**)b) - getHashElementValue(*(HashElement**)a);
}

void printWordTableStats(HashTable* wordCountTable)
{
    HashTableStats* stats = getHashTableStats(wordCountTable);
    double averageTryCount = 0;
    if (stats->totalInsertCount != 0)
        averageTryCount = (double)stats->totalInsertTryCount / stats->totalInsertCount;

    printf("Unique word count: %d\n", getHashTableSize(wordCountTable));
    printf("Remaining empty buckets: %d\n", getHashTableBucketCount(wordCountTable) - getHashTableSize(wordCountTable));
    printf("Word table load factor: %f\n", getHashTableLoadFactor(wordCountTable));
    printf("Average insertion try count: %f\n", averageTryCount);
    printf("Maximal insertion try count (%d) on these words:\n", stats->maxTryCount);
    for (int i = 0; i < stats->maxTriesWordsCount; ++i) {
        printf("%s\n", stats->maxTriesWords[i]);
    }

    destroyHashTableStats(&stats);
}

void printMostFrequentWords(HashTable* wordCountTable, int limit)
{
    HashElement** wordArray = getHashTableAsArray(wordCountTable);
    int wordArraySize = getHashTableSize(wordCountTable);
    qsort(wordArray, wordArraySize, sizeof(HashElement*), compareHashElementsDesc);

    printf("Top %d occurring words:\n", limit);
    for (int i = 0; i < wordArraySize && i < limit; ++i) {
        printf("%d. %s - %d occurrences\n", i + 1, getHashElementKey(wordArray[i]), getHashElementValue(wordArray[i]));
    }

    destroyHashTableArray(wordArray, wordArraySize);
}

int main()
{
    printf("Reading input from %s\n", inputFilename);
    FILE* inputFile = fopen(inputFilename, "r");

    if (inputFile == NULL) {
        printf("Fail! Make sure this input file exists.\n");
        return 0;
    }

    HashTable* wordCountTable = createHashTable(true);

    char* word = NULL;
    while (word = readWordFromFile(inputFile)) {
        int wordCount = 0;
        bool exists = getHashTableValue(wordCountTable, word, &wordCount);

        if (exists)
            wordCount++;
        else
            wordCount = 1;

        setHashTableValue(wordCountTable, word, wordCount);
        free(word);
    }

    fclose(inputFile);

    printWordTableStats(wordCountTable);
    printf("\n");
    printMostFrequentWords(wordCountTable, topWordsAmount);

    destroyHashTable(&wordCountTable);

    return 0;
}
