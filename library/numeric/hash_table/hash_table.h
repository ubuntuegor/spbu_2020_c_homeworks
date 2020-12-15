#ifndef SPBU_2020_C_HASH_TABLE_H
#define SPBU_2020_C_HASH_TABLE_H
#include <stdbool.h>

typedef struct HashTable HashTable;
typedef struct HashElement HashElement;

HashTable* createHashTable();
void destroyHashTable(HashTable**);

int getHashTableSize(HashTable*);
int getHashTableBucketCount(HashTable*);
double getHashTableLoadFactor(HashTable*);

bool existsInHashTable(HashTable*, long long key);
void setHashTableValue(HashTable*, long long key, int value);
bool getHashTableValue(HashTable*, long long key, int* valuePtr);
bool unsetHashTableValue(HashTable*, long long key);

HashElement** getHashTableAsArray(HashTable*);
long long getHashElementKey(HashElement*);
int getHashElementValue(HashElement*);
void destroyHashTableArray(HashElement**, int size);

#endif /* SPBU_2020_C_HASH_TABLE_H */
