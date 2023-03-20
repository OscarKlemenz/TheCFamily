/* Program: pig.c
 *  --------------
 *  pig.c is the main driver for converting words into
 *  piglatin. 
 * 
 *  Author: Oscar Klemenz
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pig.h"

char *pig(char *word)
{
    /* Function: pig
     * -------------
     * Converts a single word into pig latin
     * 
     * char *word: Pointer to the word which is being converted to pig
     * latin.
     * 
     * returns: piglatin word 
    */
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    // Checks if word begins with a vowel
    int isVowel = contains(vowels, *word);
    // If it is a vowel 'way' is added to end 
    if(isVowel)
    {
        // Allocates memory based on the size of the addition
        char *newWord = (char *)malloc((strlen(word) + 3)*sizeof(char));
        // To add to the end of the string
        char addition[] = {'w', 'a', 'y'};
        // New string created
        memcpy(newWord, word, strlen(word) * sizeof(char));
        memcpy(newWord + strlen(word), addition, 3 * sizeof(char));

        return newWord;
    }
    // If it is a constonant, moves constonants to end and adds 'ay'
    else
    {
        int len = strlen(word);
        // Allocates the max possible memory for constonants
        char *constonants = (char *)malloc(strlen(word)*sizeof(char));
        int n = 0;
        while(!isVowel && (n < len))
        {
            *constonants = *word;
            word++;
            // Checks if y is the first letter
            if(*constonants == 'y')
                isVowel = 1;
            else
            {
                constonants++;
                n++;
                // Checks if the next letter is a vowel
                isVowel = contains(vowels, *word);

                // Checks if the next letter is y
                if( *word == 'y')
                    isVowel = 1;
            }
        }
        constonants -= n;
        // Reallocates based upon string size 
        constonants = realloc(constonants, strlen(constonants) + 1);
        // Allocates memory based on the size of the addition
        char *newWord = (char *)malloc((strlen(word) + 2)*sizeof(char));
        // To be added to the end of the string
        char addition[] = {'a', 'y'};
        // combines strings
        memcpy(newWord, word, strlen(word) * sizeof(char));
        memcpy(newWord + strlen(word), constonants, (strlen(constonants)) * sizeof(char));
        memcpy(newWord + (strlen(word) + strlen(constonants)), addition, 2 * sizeof(char));

        free(constonants);
        return newWord;
    }
}

int contains(char *letters, char toCheck)
{
    /* Function: contains
     * ------------------
     * Checks if a char is in a list of chars
     * 
     * letters: List of chars to check against
     * toCheck: Char to check
     * 
     * Returns: true if char is in list, false if not
    */
    int i;
    for(i=0; i<5; i++)
    {
        if(*letters == toCheck)
        {
            return 1;
        }
        letters++;
    }
    return 0;
}