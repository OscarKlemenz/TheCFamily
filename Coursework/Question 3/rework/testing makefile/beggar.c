/* Program: beggar.c
 * -----------------
 * Contains functions to play beggar your neighbour, and any auxillary 
 * functions such, as queue functions, to deal with my chosen data structure
 * 
 * Note: For some of the smaller functions, rather than a large docstring explaination
 * I have just included a small comment above describing what it does, as some functions
 * are fairly obvious.
 * 
 * Author: Oscar Klemenz
*/
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

int finished(QUEUE *players, int Nplayers)
{
    /* Function: finished
     * ------------------
     * Checks if only one player has cards left
     * 
     * players: list of players cards
     * Nplayers: number of players
     * 
     * Returns: 1 if one player left, 0 if not
    */
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

int checkCard(QUEUE *pile)
{
    /* Function: checkCard
     * -------------------
     * Checks if the card is a picture card (11,12,13,14)
     * 
     * pile: Center pile
     * 
     * Returns: 0 if not a picture card, if it is the 2nd digit is returned
    */
    int top = peekBack(pile);
    if (top > 10)
        return (top % 10);
    else
        return 0;
}

void giveCards(QUEUE *dequeuePile, QUEUE *enqueuePile)
{
    /* Procedure: giveCards
     * -------------------
     * Swaps a card from one queue to another
     * 
     * dequeuePile: Pile to take a card from
     * enqueuePile: Pile to add a card to
    */
    int card = dequeue(dequeuePile);
    enqueue(enqueuePile, card);
}

QUEUE take_turn(QUEUE *player, QUEUE *pile)
{
    /* Function: take_turn
     * -------------------
     * Takes a single turn for a player
     * 
     * player: player taking the turn
     * pile: center pile of cards
     * 
     * Returns: If a player has to lay out penalty cards a reward will
     * be returned for the previous player to have
    */
    QUEUE reward;
    initQueue(&reward);
    // Checks the top card
    int top = checkCard(pile);
    // If top is a picture card, current player has a penalty
    if (top > 0)
    {
        // loop for the number of penalty cards to be laid
        int i;
        for(i=0;i<top;i++)
        {
            // Checks the player hasn't ran out of cards during the penalty
            if(!isEmpty(player))
            {
                // Add card to pile
                giveCards(player, pile);
                // Check players card each turn
                int newTop = checkCard(pile);
                // pentaly card, no reward, next player
                if(newTop > 0)
                    return reward;
            }
        }
        // Make whole pile reward
        while(!isEmpty(pile))
            giveCards(pile, &reward);
    }
    // If the top card is not a picture card, player lays a single card
    else
        giveCards(player, pile);
    
    return reward;
}

void deckOutput(QUEUE *pile, QUEUE *players, int currPlayer, int Nplayers)
{
    /* Procedure: deckOutput
     * --------------------
     * Prints the current state of the pile and players hands, with some formatting
     * 
     * pile: Center pile
     * players: List of players hands
     * currPlayer: The player who is currently playing
     * Nplayers: Number of players
    */
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
    /* Function: beggar
     * ----------------
     * Main driver for the beggar your neighbour game
     * 
     * Nplayers: Number of players
     * deck: Starting deck of cards (already shuffled)
     * talkative: 0 for no console output, 1 for console output
     * 
     * Returns: Number of turns
    */
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
                giveCards(&reward, &players[reciever]);

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