/* Program: piglatin.c
 * -------------------
 * Continuously asks the user for a scentence, which it then converts to
 * piglatin, until the user enters just a new line
 * 
 * Author: Oscar Klemenz
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pig.h"

int main()
{
    int exitProgram = 1;
    // Loops until user wants to exit program
    while(exitProgram)
    {
        char buffer[1000];
        char *string;
        string = malloc(1024 * sizeof(char));

        printf("Enter a sentence for translation: ");
        // Buffer checks for errors
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) 
        {
            fprintf(stderr, "Error in fgets()\n");
            exit(EXIT_FAILURE);
        }
        // The regEX is telling scanf while it is not a newline take input
        if (sscanf(buffer, "%[^\n]%*c", string) == 1) 
        {
            char *found;
            char *original_string = string;
            // Goes through each word in the string 
            while( (found = strsep(&string," ")) != NULL )
            {
                // Converts word to piglatin
                char *newWord = pig(found);
                printf("%s ", newWord);
            }
            printf("\n");
            // Resets string pointer, so it can be freed
            string = original_string;
        }
        // If user inputs empty line program is exited
        else if (buffer[0] == '\n')
        {
            printf("EXIT PROGRAM\n");
            exitProgram = 0;
        } 
        free(string);
    }


    return 0;
}