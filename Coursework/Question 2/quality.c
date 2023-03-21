/* Program: quality.c
 * ------------------
 * Driver program to find the average quality of an array of length 50
 * for 1,2,...,15 shuffles, each over 30 trials.
 * Also finds the best shuffle.
 * 
 * Author: Oscar Klemenz
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "riffle.h"

int main()
{
    FILE *out_file = fopen("quality.txt", "w"); // write only

    // test for files not existing.
    if (out_file == NULL)
    {  
        printf("Error! Could not open file\n");
        exit(-1);
    }
    // Sets the seed for random
    srand(time(NULL));
    
    fprintf(out_file, "TESTING QUALITY OF RIFFLE SHUFFLE\n"); 
    fprintf(out_file, "Average of N shuffles: \n");
    // Allocates memory for an array of averages
    float *avg = malloc(15 * sizeof(float));
    if (avg == NULL) {
        // Failed to allocate memory, return failure
        printf("Error! Could not allocate memory\n");
        exit(-1);
    }
    // Shuffle array 1, 2, ... 15
    int i;
    float smallest = 1.0;
    int smallestPtr = 0;
    for(i=1;i<16;i++)
    {
        // Checks the quality of i shuffles over 30 trials
        float qual = average_quality(50, i, 30);
        fprintf(out_file, "%d: %f\n", i, qual);
        // Checks if it is the highest qwuality
        if(qual < smallest)
        {
            smallest = qual;
            smallestPtr = i;
        }

        *avg = qual;
        avg++;
    }
    avg -= 15;

    // Outputs the best quality
    fprintf(out_file, "The best quality shuffle number is: %d\nWith a quality of: %f", smallestPtr, smallest);

    free(avg);

    return 0;
}