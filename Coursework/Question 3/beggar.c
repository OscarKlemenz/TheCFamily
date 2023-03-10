#include <stdio.h>
#include <stdlib.h>
// MAX_SIZE is 36, as min possible division of cards is 52 / 2
#define MAX_SIZE 36

struct Queue {
    int arr[MAX_SIZE];
    int front, rear;
};
typedef struct Queue QUEUE;

// Function to initialize a new queue
void initQueue(QUEUE *q) {
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is empty
int isEmpty(struct Queue *q) {
    return (q->front == -1 && q->rear == -1);
}

// Function to check if the queue is full
int isFull(QUEUE *q) {
    return (q->rear + 1) % MAX_SIZE == q->front;
}

// Function to add an element to the rear of the queue
void enqueue(QUEUE *q, int element) {
    if (isFull(q)) {
        printf("Queue is full.\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX_SIZE;
    }
    q->arr[q->rear] = element;
}

// Function to remove an element from the front of the queue
int dequeue(QUEUE *q) {
    int element;
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return -1;
    }
    element = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_SIZE;
    }
    return element;
}

// Function to print the elements of the queue
void printQueue(QUEUE *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = q->front; i != q->rear; i = (i + 1) % MAX_SIZE) {
        printf("%d ", q->arr[i]);
    }
    printf("%d\n", q->arr[q->rear]);
}

// Checks if only one player has cards left
int finished(QUEUE *players, int Nplayers)
{
    int numEmpty = 0;
    int withCards = -1;
    // Loop through all players
    int i;
    for(i=0;i<Nplayers;i++)
    {
        // Check if queue is empty
        if(isEmpty(players))
            numEmpty++;
        else 
            withCards = i;
        players++;
    }
    players -= Nplayers;

    if(numEmpty == (Nplayers - 1))
        return withCards;
    else
        return 0;
}

// Main driver function for beggar your neighbour game
int beggar(int Nplayers, int *deck, int talkative)
{
    int turns = 0;
    QUEUE *players = (QUEUE *)malloc(Nplayers * sizeof(QUEUE));
    // Initialise player decks
    int i;
    for(i=0;i<Nplayers;i++)
    {
        QUEUE newQueue;
        initQueue(&newQueue);
        players[i] = newQueue;
    }

    // Deal cards
    int currPlayer = 0;
    for(i=0;i<52;i++)
    {
        enqueue(&players[i], *deck);
        deck++;
        currPlayer++;
        if(currPlayer == Nplayers)
            currPlayer = 0;
    }

    return turns;
}

int main()
{
    int N = 3;

    QUEUE *players = (QUEUE *)malloc(N * sizeof(QUEUE));

    int i;
    for(i=0;i<N;i++)
    {
        QUEUE newQueue;
        initQueue(&newQueue);
        enqueue(&newQueue, 5);
        players[i] = newQueue;
    }

    printQueue(&players[0]);
    dequeue(&players[2]);
    dequeue(&players[1]);

    int f = finished(players, 3);

    printf("%d", f);

    return 0;
}