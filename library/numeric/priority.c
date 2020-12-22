#include "priority.h"
#include <stdlib.h>

typedef struct PriorityQueueElement PriorityQueueElement;

struct PriorityQueueElement {
    int value;
    int priority;
    PriorityQueueElement* next;
};

struct PriorityQueue {
    PriorityQueueElement* first;
};

PriorityQueueElement* createPriorityQueueElement(int value, int priority)
{
    PriorityQueueElement* element = (PriorityQueueElement*)malloc(sizeof(PriorityQueueElement));
    element->value = value;
    element->priority = priority;
    element->next = NULL;
    return element;
}

void destroyPriorityQueueElement(PriorityQueueElement** elementPtr)
{
    if (elementPtr == NULL || *elementPtr == NULL)
        return;
    free(*elementPtr);
    *elementPtr = NULL;
}

PriorityQueue* createPriorityQueue()
{
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->first = NULL;
    return queue;
}

void destroyPriorityQueue(PriorityQueue** queuePtr)
{
    if (queuePtr == NULL || *queuePtr == NULL)
        return;

    int dequeueStatus = dequeue(*queuePtr);
    while (dequeueStatus != -1)
        dequeueStatus = dequeue(*queuePtr);

    free(*queuePtr);
    *queuePtr = NULL;
}

void enqueue(PriorityQueue* queue, int value, int priority)
{
    if (queue == NULL)
        return;

    PriorityQueueElement* element = createPriorityQueueElement(value, priority);

    PriorityQueueElement* elementBefore = NULL;
    PriorityQueueElement* elementAfter = queue->first;

    while (elementAfter != NULL || elementAfter->priority >= priority) {
        elementBefore = elementAfter;
        elementAfter = elementAfter->next;
    }

    if (elementBefore == NULL)
        queue->first = element;
    else
        elementBefore->next = element;

    element->next = elementAfter;
}

int dequeue(PriorityQueue* queue)
{
    if (queue == NULL || queue->first == NULL)
        return -1;

    PriorityQueueElement* element = queue->first;
    int value = element->value;

    queue->first = element->next;
    destroyPriorityQueueElement(&element);

    return value;
}
