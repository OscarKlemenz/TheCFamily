#include <stdio.h>
#include <stdlib.h>
#include "beggar.h"

int main()
{
    FILE *out_file = fopen("statistics.txt", "w"); // write only

    // test for files not existing.
    if (out_file == NULL)
    {  
        printf("Error! Could not open file\n");
        exit(-1); // must include stdlib.h
    }
    
    fprintf(out_file, "Below are some statistics generated about the number of turns taken from playing games with 2,3..,10 players, playing 100 games with each number of players\n"); 
    
    STATS *stats = statistics(10, 100);

    fprintf(out_file, "Shortest: %d\n", stats->shortest);
    fprintf(out_file, "Longest: %d\n", stats->longest);
    fprintf(out_file, "Average: %f\n", stats->average);

    free(stats);

    return 0;
}