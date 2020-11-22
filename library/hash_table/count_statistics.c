#include "count_statistics.h"
#include "../string/io.h"
#include <stdlib.h>

void countInsertStats(HashTableStats* stats, int tryCount, char* key)
{
    stats->totalInsertCount++;
    stats->totalInsertTryCount += tryCount;

    if (tryCount > stats->maxTryCount) {
        stats->maxTryCount = tryCount;

        if (stats->maxTriesWords != NULL)
            freeStringArray(stats->maxTriesWords, stats->maxTriesWordsCount);

        stats->maxTriesWords = initializeStringArray(key);
        stats->maxTriesWordsCount = 1;
    } else if (tryCount == stats->maxTryCount) {
        stats->maxTriesWords = appendToStringArray(stats->maxTriesWords, stats->maxTriesWordsCount, key);
        stats->maxTriesWordsCount++;
    }
}
