/* Program: byn.c
 * -----------------
 * Prints the statistics for games with 2,3,4,...,N 
 * players using at least 100 trials each. Your byn program should 
 * take two command line arguments: the maximum number of players and the number of trials.
 * 
 * Author: Oscar Klemenz
*/
#include <stdio.h>
#include <stdlib.h>
#include "beggar.h"

int main(int argc, char *argv[])
{
    // Checks user has entered the maximum number of players and trials
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <max_players> <num_trails>\n", argv[0]);
        exit(1);
    }
    int maxPlayers = atoi(argv[1]);
    int trials = atoi(argv[2]);

    FILE *out_file = fopen("statistics.txt", "w"); // write only
    // test for files not existing.
    if (out_file == NULL)
    {  
        printf("Error! Could not open file\n");
        exit(-1);
    }
    // Calculates stats and generates a file output
    fprintf(out_file, "Below are some statistics generated about the number of turns taken from playing games with 2,3..,%d players, playing %d games with each number of players\n", maxPlayers, trials); 

    STATS *stats = statistics(maxPlayers, trials);

    fprintf(out_file, "Shortest: %d\n", stats->shortest);
    fprintf(out_file, "Longest: %d\n", stats->longest);
    fprintf(out_file, "Average: %f\n", stats->average);

    free(stats);

    return 0;
}