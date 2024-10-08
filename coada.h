#pragma once

#include "liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct QueueNode{
    Match* val;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue{
    QueueNode *front, *rear;
} Queue;

Queue *createQueue();

void enQueue(Queue *q, Match *v);

Match *deQueue(Queue *q);

int isQueueEmpty(Queue *q);

void deleteQueue(Queue *q);