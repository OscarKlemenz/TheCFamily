/* Program: test_pig.c
 * -------------------
 * Runs tests on pig.c, using 7 prefined words
 * 
 * Author: Oscar Klemenz
*/
#include <stdio.h>
#include "pig.h"

int main()
{
    // List of examples
    char examples[7][10] = {"happy", "duck", "glove", "evil",
    "eight", "yowler", "crystal"};
    
    int i;
    for(i=0;i<7;i++)
    {
        char *word;
        // Allocates memory for word 
        word = malloc(strlen(examples[i]) * sizeof(char));
        // Sets the pointer 
        word = examples[i];
        // Converts the word
        char *newWord = pig(word);
        printf("%s => %s\n", word, newWord);

        free(newWord);
    }
    return 0;
}