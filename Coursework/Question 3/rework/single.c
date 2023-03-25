#include <stdio.h>
#include <stdlib.h>
#include "beggar.h"
#include "riffle.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num_players>\n", argv[0]);
        exit(1);
    }

    int numPlayers = atoi(argv[1]);

    // TODO: Write your code here
    printf("Num players %d\n", numPlayers);

    // Generate a deck of cards
    int *deck = (int *)malloc(52 * sizeof(int));

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
    // Shuffle the deck of cards
    riffle(deck, 52, sizeof(int), 50);

    // Call function
    beggar(numPlayers, deck, 1);
    free(deck);
    return 0;

}