#include "../library/hash_table/hash_table.h"
#include "../library/string/io.h"
#include <stdio.h>
#include <stdlib.h>

const char inputFilename[] = "hw6task1_input.txt";

int compareHashElementsDesc(const void* a, const void* b)
{
    return getHashElementValue(*(HashElement**)b) - getHashElementValue(*(HashElement**)a);
}

void printWordTableStats(HashTable* wordCountTable)
{
    HashTableStats* stats = getHashTableStats(wordCountTable);
    double averageTryCount = (double)stats->insertTryCount / stats->insertOperationCount;

    printf("Unique word count: %d\n", getHashTableSize(wordCountTable));
    printf("Remaining empty buckets: %d\n", getHashTableBucketCount(wordCountTable) - getHashTableSize(wordCountTable));
    printf("Word table load factor: %f\n", getHashTableLoadFactor(wordCountTable));
    printf("Average insertion try count: %f\n", averageTryCount);
    printf("Maximal insertion try count (%d) on these words:\n", stats->maxTryCountPerOperation);
    for (int i = 0; i < stats->maxTryCountWordCount; ++i) {
        printf("%s\n", stats->maxTryCountWords[i]);
    }

    destroyHashTableStats(&stats);
}

void printTopTenWords(HashTable* wordCountTable)
{
    HashElement** wordArray = getHashTableAsArray(wordCountTable);
    int wordArraySize = getHashTableSize(wordCountTable);
    qsort(wordArray, wordArraySize, sizeof(HashElement*), compareHashElementsDesc);

    printf("Top 10 occurring words:\n");
    for (int i = 0; i < wordArraySize && i < 10; ++i) {
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
        getHashTableValue(wordCountTable, word, &wordCount);
        wordCount++;
        setHashTableValue(wordCountTable, word, wordCount);
        free(word);
    }

    fclose(inputFile);

    printWordTableStats(wordCountTable);
    printf("\n");
    printTopTenWords(wordCountTable);

    destroyHashTable(&wordCountTable);

    return 0;
}
