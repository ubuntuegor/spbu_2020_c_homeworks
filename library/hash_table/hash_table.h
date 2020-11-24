#ifndef SPBU_2020_C_HASH_TABLE_H
#define SPBU_2020_C_HASH_TABLE_H
#include <stdbool.h>

typedef struct HashTable HashTable;
typedef struct HashElement HashElement;

typedef struct HashTableStats {
    int totalInsertCount;
    int totalInsertTryCount;
    int maxTryCount;
    char** maxTriesWords;
    int maxTriesWordsCount;
} HashTableStats;

HashTable* createHashTable(bool shouldCountStats);
void destroyHashTable(HashTable**);

int getHashTableSize(HashTable*);
int getHashTableBucketCount(HashTable*);
double getHashTableLoadFactor(HashTable*);

HashTableStats* getHashTableStats(HashTable*);
void destroyHashTableStats(HashTableStats**);

void setHashTableHashFunction(HashTable*, int (*hashFunction)(char* key, int modulus));
void setHashTableTryFunction(HashTable*, int (*tryFunction)(int n, int modulus));

bool existsInHashTable(HashTable*, char* key);
void setHashTableValue(HashTable*, char* key, int value);
bool getHashTableValue(HashTable*, char* key, int* valuePtr);
bool unsetHashTableValue(HashTable*, char* key);

HashElement** getHashTableAsArray(HashTable*);
char* getHashElementKey(HashElement*);
int getHashElementValue(HashElement*);
void destroyHashTableArray(HashElement**, int size);

#endif /* SPBU_2020_C_HASH_TABLE_H */
