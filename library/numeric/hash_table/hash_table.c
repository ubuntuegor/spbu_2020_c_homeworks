#include "hash_table.h"
#include "../../string/io.h"
#include "default_hash_functions.h"
#include <stdlib.h>

const double expandTableLimit = 0.7;
const double shrinkTableLimit = 0.2;

struct HashTable {
    int bucketCount;
    int size;
    HashElement** buckets;
    int (*hashFunction)(long long key, int modulus);
    int (*tryFunction)(int n, int modulus);
};

struct HashElement {
    bool removed;
    long long key;
    int value;
};

HashElement* createHashElement(long long key, int value)
{
    HashElement* element = (HashElement*)malloc(sizeof(HashElement));
    element->removed = false;
    element->key = key;
    element->value = value;
    return element;
}

void destroyHashElement(HashElement** elementPtr)
{
    if (elementPtr == NULL || *elementPtr == NULL)
        return;
    HashElement* element = *elementPtr;
    free(element);
    *elementPtr = NULL;
}

HashTable* createHashTableWithBucketCount(int bucketCount)
{
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->bucketCount = bucketCount;
    table->size = 0;
    table->buckets = (HashElement**)calloc(bucketCount, sizeof(HashElement*));
    table->hashFunction = integerHash;
    table->tryFunction = squareTries;
    return table;
}

HashTable* createHashTable()
{
    return createHashTableWithBucketCount(1);
}

void destroyHashTable(HashTable** tablePtr)
{
    if (tablePtr == NULL || *tablePtr == NULL)
        return;

    HashTable* table = *tablePtr;

    for (int i = 0; i < table->bucketCount; ++i)
        destroyHashElement(&table->buckets[i]);

    free(table->buckets);
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

HashElement* findElementInHashTable(HashTable* table, long long key)
{
    if (table == NULL)
        return NULL;

    int hashCode = table->hashFunction(key, table->bucketCount);
    int tryNumber = 0;

    int index = hashCode + table->tryFunction(tryNumber, table->bucketCount);
    index %= table->bucketCount;
    HashElement* element = table->buckets[index];

    while (element != NULL && tryNumber < table->bucketCount) {
        if (!element->removed) {
            if (element->key == key)
                return element;
        }

        tryNumber++;
        index = hashCode + table->tryFunction(tryNumber, table->bucketCount);
        index %= table->bucketCount;
        element = table->buckets[index];
    }

    return NULL;
}

HashElement* insertElementIntoHashTable(HashTable* table, long long key, int value)
{
    if (table == NULL)
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
            insertElementIntoHashTable(table, element->key, element->value);
        destroyHashElement(&oldBuckets[i]);
    }

    free(oldBuckets);
}

bool existsInHashTable(HashTable* table, long long key)
{
    if (table == NULL)
        return false;

    HashElement* element = findElementInHashTable(table, key);

    return element != NULL;
}

void setHashTableValue(HashTable* table, long long key, int value)
{
    if (table == NULL)
        return;

    HashElement* element = findElementInHashTable(table, key);

    if (element != NULL)
        element->value = value;
    else {
        if (getHashTableLoadFactor(table) >= expandTableLimit)
            resizeHashTable(table, table->bucketCount * 2);

        insertElementIntoHashTable(table, key, value);
    }
}

bool getHashTableValue(HashTable* table, long long key, int* valuePtr)
{
    if (table == NULL || valuePtr == NULL)
        return false;

    HashElement* element = findElementInHashTable(table, key);
    if (element == NULL)
        return false;

    *valuePtr = element->value;

    return true;
}

bool unsetHashTableValue(HashTable* table, long long key)
{
    if (table == NULL)
        return false;

    HashElement* element = findElementInHashTable(table, key);
    if (element == NULL)
        return false;

    element->removed = true;
    table->size--;

    if (getHashTableLoadFactor(table) <= shrinkTableLimit && table->bucketCount > 1)
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

long long getHashElementKey(HashElement* element)
{
    if (element == NULL)
        return 0;
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
