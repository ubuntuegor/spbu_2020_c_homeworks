#ifndef SPBU_2020_C_NUMERIC_PRIORITY_H
#define SPBU_2020_C_NUMERIC_PRIORITY_H

typedef struct PriorityQueue PriorityQueue;

PriorityQueue* createPriorityQueue();
void destroyPriorityQueue(PriorityQueue**);

void enqueue(PriorityQueue*, int value, int priority);
int dequeue(PriorityQueue*);

#endif /* SPBU_2020_C_NUMERIC_PRIORITY_H */