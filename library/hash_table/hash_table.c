#include "hash_table.h"
#include "../string/io.h"
#include "default_hash_functions.h"
#include <stdlib.h>
#include <string.h>

struct HashTable {
    int bucketCount;
    int size;
    HashElement** buckets;
    int (*hashFunction)(char* key, int modulus);
    int (*tryFunction)(int n, int modulus);
    bool countStats;
    HashTableStats* stats;
};

struct HashElement {
    bool removed;
    char* key;
    int value;
};

HashElement* createHashElement(char* key, int value)
{
    HashElement* element = (HashElement*)malloc(sizeof(HashElement));
    char* keyCopy = (char*)calloc(strlen(key) + 1, sizeof(char));
    strcpy(keyCopy, key);
    element->removed = false;
    element->key = keyCopy;
    element->value = value;
    return element;
}

void destroyHashElement(HashElement** elementPtr)
{
    if (elementPtr == NULL || *elementPtr == NULL)
        return;
    HashElement* element = *elementPtr;
    free(element->key);
    free(element);
    *elementPtr = NULL;
}

HashTableStats* createHashTableStats()
{
    HashTableStats* stats = (HashTableStats*)malloc(sizeof(HashTableStats));
    stats->insertOperationCount = 0;
    stats->insertTryCount = 0;
    stats->maxTryCountPerOperation = 0;
    stats->maxTryCountWords = NULL;
    stats->maxTryCountWordCount = 0;
    return stats;
}

HashTableStats* getHashTableStats(HashTable* table)
{
    if (table == NULL)
        return NULL;

    HashTableStats* statsCopy = (HashTableStats*)malloc(sizeof(HashTableStats));
    memcpy(statsCopy, table->stats, sizeof(HashTableStats));

    statsCopy->maxTryCountWords = (char**)calloc(statsCopy->maxTryCountWordCount, sizeof(char*));
    for (int i = 0; i < table->stats->maxTryCountWordCount; ++i) {
        char* word = table->stats->maxTryCountWords[i];
        statsCopy->maxTryCountWords[i] = (char*)calloc(strlen(word) + 1, sizeof(char));
        strcpy(statsCopy->maxTryCountWords[i], word);
    }

    return statsCopy;
}

void destroyHashTableStats(HashTableStats** statsPtr)
{
    if (statsPtr == NULL || *statsPtr == NULL)
        return;

    HashTableStats* stats = *statsPtr;

    freeStringArray(stats->maxTryCountWords, stats->maxTryCountWordCount);
    free(stats);

    *statsPtr = NULL;
}

HashTable* createHashTableWithBucketCount(bool countStats, int bucketCount)
{
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->bucketCount = bucketCount;
    table->size = 0;
    table->buckets = (HashElement**)calloc(bucketCount, sizeof(HashElement*));
    table->hashFunction = rollingHashPrime2;
    table->tryFunction = squareTries;
    table->countStats = countStats;
    table->stats = createHashTableStats();
    return table;
}

HashTable* createHashTable(bool countStats)
{
    return createHashTableWithBucketCount(countStats, 1);
}

void destroyHashTable(HashTable** tablePtr)
{
    if (tablePtr == NULL || *tablePtr == NULL)
        return;

    HashTable* table = *tablePtr;

    for (int i = 0; i < table->bucketCount; ++i)
        destroyHashElement(&table->buckets[i]);

    free(table->buckets);
    destroyHashTableStats(&table->stats);
    free(table);

    *tablePtr = NULL;
}

int getHashTableSize(HashTable* table)
{
    if (table == NULL)
        return 0;
    return table->size;
}

int getHashTableBucketCount(HashTable* table)
{
    if (table == NULL)
        return 0;
    return table->bucketCount;
}

double getHashTableLoadFactor(HashTable* table)
{
    if (table == NULL)
        return 0;
    return (double)getHashTableSize(table) / (double)getHashTableBucketCount(table);
}

void setHashTableHashFunction(HashTable* table, int (*hashFunction)(char* key, int modulus))
{
    if (table == NULL)
        return;
    table->hashFunction = hashFunction;
}

void setHashTableTryFunction(HashTable* table, int (*tryFunction)(int n, int modulus))
{
    if (table == NULL)
        return;
    table->tryFunction = tryFunction;
}

HashElement* findElementInHashTable(HashTable* table, char* key)
{
    if (table == NULL || key == NULL)
        return NULL;

    int hashCode = table->hashFunction(key, table->bucketCount);
    int tryNumber = 0;

    int index = hashCode + table->tryFunction(tryNumber, table->bucketCount);
    index %= table->bucketCount;
    HashElement* element = table->buckets[index];

    while (element != NULL && tryNumber < table->bucketCount) {
        if (element->removed)
            continue;
        if (strcmp(element->key, key) == 0)
            return element;

        tryNumber++;
        index = hashCode + table->tryFunction(tryNumber, table->bucketCount);
        index %= table->bucketCount;
        element = table->buckets[index];
    }

    return NULL;
}

HashElement* insertElementIntoHashTable(HashTable* table, char* key, int value, bool countStats)
{
    if (table == NULL || key == NULL)
        return NULL;

    int hashCode = table->hashFunction(key, table->bucketCount);
    int tryNumber = 0;

    int index = hashCode + table->tryFunction(tryNumber, table->bucketCount);
    index %= table->bucketCount;
    HashElement* element = table->buckets[index];

    while (element != NULL && !element->removed) {
        tryNumber++;
        index = hashCode + table->tryFunction(tryNumber, table->bucketCount);
        index %= table->bucketCount;
        element = table->buckets[index];
    }

    if (element != NULL)
        destroyHashElement(&element);

    element = createHashElement(key, value);
    table->buckets[index] = element;
    table->size++;

    if (countStats) {
        int tryCount = tryNumber + 1;
        HashTableStats* stats = table->stats;
        stats->insertOperationCount++;
        stats->insertTryCount += tryCount;

        if (tryCount > stats->maxTryCountPerOperation) {
            stats->maxTryCountPerOperation = tryCount;

            if (stats->maxTryCountWords != NULL)
                freeStringArray(stats->maxTryCountWords, stats->maxTryCountWordCount);

            stats->maxTryCountWordCount = 1;
            stats->maxTryCountWords = (char**)calloc(1, sizeof(char*));
            stats->maxTryCountWords[0] = (char*)calloc(strlen(key) + 1, sizeof(char));
            strcpy(stats->maxTryCountWords[0], key);
        } else if (tryCount == stats->maxTryCountPerOperation) {
            int index = stats->maxTryCountWordCount;
            stats->maxTryCountWordCount++;
            stats->maxTryCountWords = (char**)realloc(stats->maxTryCountWords, stats->maxTryCountWordCount * sizeof(char*));
            stats->maxTryCountWords[index] = (char*)calloc(strlen(key) + 1, sizeof(char));
            strcpy(stats->maxTryCountWords[index], key);
        }
    }

    return element;
}

void resizeHashTable(HashTable* table, int newBucketCount)
{
    if (table == NULL)
        return;

    HashElement** oldBuckets = table->buckets;
    int oldBucketsSize = table->bucketCount;

    table->bucketCount = newBucketCount;
    table->size = 0;
    table->buckets = (HashElement**)calloc(newBucketCount, sizeof(HashElement*));

    for (int i = 0; i < oldBucketsSize; ++i) {
        HashElement* element = oldBuckets[i];
        if (element != NULL && !element->removed)
            insertElementIntoHashTable(table, element->key, element->value, false);
        destroyHashElement(&oldBuckets[i]);
    }

    free(oldBuckets);
}

bool existsInHashTable(HashTable* table, char* key)
{
    if (table == NULL || key == NULL)
        return false;

    HashElement* element = findElementInHashTable(table, key);

    return element != NULL;
}

void setHashTableValue(HashTable* table, char* key, int value)
{
    if (table == NULL || key == NULL)
        return;

    HashElement* element = findElementInHashTable(table, key);

    if (element != NULL)
        element->value = value;
    else {
        if (getHashTableLoadFactor(table) >= 0.7)
            resizeHashTable(table, table->bucketCount * 2);

        insertElementIntoHashTable(table, key, value, table->countStats);
    }
}

bool getHashTableValue(HashTable* table, char* key, int* valuePtr)
{
    if (table == NULL || key == NULL || valuePtr == NULL)
        return false;

    HashElement* element = findElementInHashTable(table, key);
    if (element == NULL)
        return false;

    *valuePtr = element->value;

    return true;
}

bool unsetHashTableValue(HashTable* table, char* key)
{
    if (table == NULL || key == NULL)
        return false;

    HashElement* element = findElementInHashTable(table, key);
    if (element == NULL)
        return false;

    element->removed = true;
    table->size--;

    if (getHashTableLoadFactor(table) <= 0.20 && table->bucketCount > 1)
        resizeHashTable(table, table->bucketCount / 2);

    return true;
}

HashElement** getHashTableAsArray(HashTable* table)
{
    if (table == NULL)
        return NULL;

    HashElement** elementList = (HashElement**)calloc(table->size, sizeof(HashElement*));
    int index = 0;

    for (int i = 0; i < table->bucketCount && index < table->size; ++i) {
        HashElement* element = table->buckets[i];
        if (element != NULL && !element->removed) {
            elementList[index] = createHashElement(element->key, element->value);
            index++;
        }
    }

    return elementList;
}

char* getHashElementKey(HashElement* element)
{
    if (element == NULL)
        return NULL;
    return element->key;
}

int getHashElementValue(HashElement* element)
{
    if (element == NULL)
        return 0;
    return element->value;
}

void destroyHashTableArray(HashElement** elementList, int size)
{
    if (elementList == NULL)
        return;

    for (int i = 0; i < size; ++i)
        destroyHashElement(&elementList[i]);

    free(elementList);
}