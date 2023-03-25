#include <stdio.h>
#include <stdlib.h>
#include "riffle.h"

// MAX_SIZE is 52, as max possible amount of cards is 52
#define MAX_SIZE 52

struct Queue {
    int arr[MAX_SIZE];
    int front, rear;
};
typedef struct Queue QUEUE;

struct Stats{
    int shortest, longest;
    float average;
};
typedef struct Stats STATS;

void initQueue(QUEUE *);
int isEmpty(QUEUE *);
int isFull(QUEUE *);
void enqueue(QUEUE *, int);
int dequeue(QUEUE *);
int peek(QUEUE *);
int peekBack(QUEUE *);
void printQueue(QUEUE *);
int finished(QUEUE *, int);
QUEUE take_turn(QUEUE *, QUEUE *);
int beggar(int, int *, int);
void deckOutput(QUEUE *, QUEUE *, int, int);
STATS *statistics(int , int);
