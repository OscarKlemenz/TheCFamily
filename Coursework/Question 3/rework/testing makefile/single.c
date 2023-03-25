/* Program: single.c
 * -----------------
 * Takes the number of players as a command line argument and prints
 * the details of a beggar your neighbour game played with that many
 * players.
 * 
 * Author: Oscar Klemenz
*/
#include <stdio.h>
#include <stdlib.h>
#include "beggar.h"
#include "riffle.h"

int main(int argc, char *argv[]) 
{
    // Checks user has entered a player number in the command line
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num_players>\n", argv[0]);
        exit(1);
    }

    int numPlayers = atoi(argv[1]);

    // Generate a deck of cards
    int *deck = (int *)malloc(52 * sizeof(int));
    if (deck == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    int i;
    for(i=2;i<15;i++)
    {
        int y;
        for(y=0;y<4;y++)
            *(deck++) = i;
    }
    deck -= 52;
    // Shuffle the deck of cards
    riffle(deck, 52, sizeof(int), 50);

    // Plays on game of beggar your neighbour
    beggar(numPlayers, deck, 1);
    free(deck);
    return 0;

}