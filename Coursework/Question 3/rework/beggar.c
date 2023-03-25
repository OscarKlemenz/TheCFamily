#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "beggar.h"

// Function to initialize a new queue
void initQueue(QUEUE *q) {
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is empty
int isEmpty(QUEUE *q) {
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

// Checks the card at the front of the queue
int peek(QUEUE *q)
{
    int element = q->arr[q->front];
    return element;
}

// Checks card at the back of the queue
int peekBack(QUEUE *q)
{
    if(isEmpty(q))
        return -1;
    else
    {
        int element = q->arr[q->rear];
        return element;
    }
}


// Function to print the elements of the queue
void printQueue(QUEUE *q) {
    if (isEmpty(q)) {
        printf("\n");
        return;
    }
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
            // Cant have player 0 returning 0
            withCards = i + 1;
        players++;
    }
    players -= Nplayers;

    if(numEmpty == (Nplayers - 1))
        return withCards;
    else
        return 0;
}

// Checks if the card is a picture card
int checkCard(QUEUE *pile)
{
    // peek card just added
    int top = peekBack(pile);
    // Mod by 10 and return remainder
    if (top > 10)
        return (top % 10);
    else
        return 0;
}

// Takes a turn for a player
QUEUE take_turn(QUEUE *player, QUEUE *pile)
{
    QUEUE reward;
    initQueue(&reward);
    // Check the top card - Make function to do this
    int top = checkCard(pile);
    // If return non-zero
    if (top > 0)
    {
        // loop for the number returned
        int i;
        for(i=0;i<top;i++)
        {
            // Checks the player hasn't ran out of cards during
            // penalty
            if(!isEmpty(player))
            {
                // Add card to pile
                int card = dequeue(player);
                enqueue(pile, card);
                // Check players card each turn
                int newTop = checkCard(pile);
                if(newTop > 0)
                {
                    // pentaly card, no reward, next player
                    return reward;
                }
            }
        }
        // Make whole pile reward
        while(!isEmpty(pile))
        {
            // Dequeue pile and enqueue to reward
            int card = dequeue(pile);
            enqueue(&reward, card);
        }
    }
    // else If is zero
    else
    {
        // lay one card
        int card = dequeue(player);
        enqueue(pile, card);  
    }     
    // return no reward
    return reward;
}

void deckOutput(QUEUE *pile, QUEUE *players, int currPlayer, int Nplayers)
{
    printf("Pile: ");
    printQueue(pile);
    int y;
    for(y=0;y<Nplayers;y++)
    {
        if(y == currPlayer)
            printf("*   ");
        else
            printf("    ");
        printf("%d: ", y);
        printQueue(&players[y]);
    }
}

// Main driver function for beggar your neighbour game
int beggar(int Nplayers, int *deck, int talkative)
{   
    int turns = 1;
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
        enqueue(&players[currPlayer], *deck);
        deck++;
        currPlayer++;
        if(currPlayer == Nplayers)
            currPlayer = 0;
    }
    // Initialises the pile
    QUEUE pile;
    initQueue(&pile);

    currPlayer = 0;
    if(talkative)
        printf("Turn %d\n", turns);
    // While theres more than one player left
    while(!finished(players, Nplayers))
    {
        int penaltyTurn = 0;
        int skippedPenalty = 0;
        // Players turn is skipped if they've ran out of cards
        if(!isEmpty(&players[currPlayer]))
        {
            // Formatting
            if(talkative)
            {

                int topCard = peekBack(&pile);
                if(topCard == -1)
                    printf("Pile now empty, ");
                else
                    printf("Top card is %d, ", topCard);
                // List the top card,
                printf("so player %d should lay ", currPlayer);
                int pentalty = checkCard(&pile);
                if(pentalty == 0)
                {
                    printf("a single card\n");
                    penaltyTurn = 0;
                }
                else
                {
                    printf("%d penalty card(s)\n", pentalty);
                    penaltyTurn = 1;
                }
                // Outputs deck state
                deckOutput(&pile, players, currPlayer, Nplayers);
            }
            /* Need a variable to tell if its a penalty turn, and if the next player paid it off */
            
            // Player takes a turn
            QUEUE reward = take_turn(&players[currPlayer], &pile);

            // If there is a reward, give to previous player
            int reciever;
            if(!isEmpty(&reward))
            {
                reciever = currPlayer;
                // Finds the last player who hasn't ran out of cards
                do
                {
                    if(reciever == 0)
                        reciever = Nplayers - 1;
                    else
                        reciever--;
                } while (isEmpty(&players[reciever]));

            }
            else if (penaltyTurn)
            {   
                skippedPenalty = 1;
            }

            while(!isEmpty(&reward))
            {
                // Give to previous player
                int card = dequeue(&reward);
                // PRINT OFF CARDS 
                enqueue(&players[reciever], card);
            }

            turns++;
            if(talkative)
                printf("Turn %d\n", turns);
            if (talkative && skippedPenalty)
            {
                printf("Player %d laid a pentalty card, ", currPlayer);
                skippedPenalty = 0;
            }
            else if (talkative && !skippedPenalty && penaltyTurn)
            {
                printf("Player %d laid their cards without drawing a penalty card, cards are given to player %d", currPlayer, reciever);
            }
        }
        // Move on to the next player
        currPlayer++;
        if(currPlayer == Nplayers)
            currPlayer = 0;
    }

    int winner = (finished(players, Nplayers) - 1);

    if(talkative)
    {
        printf("GAME OVER!\nPlayer %d wins\n", winner);
        deckOutput(&pile, players, winner, Nplayers);
    }

    free(players);
    return turns;
}

STATS *statistics(int Nplayers, int games)
{
    STATS *stats = (STATS*)malloc(sizeof(STATS));
    stats->shortest = INT_MAX;
    stats->longest = -1;
    stats->average = -1;

    // Generate a deck of cards
    int *deck = (int *)malloc(52 * sizeof(int));

    int totalTurns = 0;

    int i;
    for(i=2;i<15;i++)
    {
        int y;
        for(y=0;y<4;y++)
        {
            *deck = i;
            deck++;
        }
    }
    deck -= 52;
    // Runs beggar for 2,3..,Nplayers for games times
    for(i=2;i<(Nplayers+1);i++)
    {
        int y;
        for(y=0;y<games;y++)
        {
            // Shuffle the deck of cards
            riffle(deck, 52, sizeof(int), 50);
            int turns = beggar(i, deck, 0);

            if (turns < stats->shortest)
                stats->shortest = turns;
            if (turns > stats->longest)
                stats->longest = turns;

            totalTurns += turns;
        }
    }

    free(deck);

    stats->average = totalTurns / ((Nplayers -1) * games);
    

    return stats;
}