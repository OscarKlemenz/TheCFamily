#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pig.h"

int main()
{
    int exitProgram = 1;
    /* Loops until user wants to exit program */
    while(exitProgram != 0)
    {
        char buffer[1000];
        char *string;
        string = malloc(1024 * sizeof(char));

        printf("Enter a sentence for translation: ");
        /* Buffer checks for errors */
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) 
        {
            fprintf(stderr, "Error in fgets()\n");
            exit(EXIT_FAILURE);
        }
        /* The regEX is telling scanf while it is not a newline
        take input */
        if (sscanf(buffer, "%[^\n]%*c", string) == 1) 
        {
            char *found;
            /* Goes through each word in the string */
            while( (found = strsep(&string," ")) != NULL )
            {
                /* Converts word to piglatin */
                char *newWord = pig(found);
                printf("%s ", newWord);
            }
            printf("\n");
        }
        /* If user inputs empty line program is exited */
        else if (buffer[0] == '\n')
        {
            printf("EXIT PROGRAM\n");
            exitProgram = 0;
        } 

        free(string);
    }


    return 0;
}

/*
    char *word;
    word = malloc(1024 * sizeof(char));


    printf("Enter a word:");
    scanf("%1023s", word);


    word = realloc(word, strlen(word) + 1);

    char *newWord = pig(word);

    printf("%s => %s\n", word, newWord);

    free(word);
    free(newWord);
*/