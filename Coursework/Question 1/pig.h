#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *pig(char *);
int contains(char *, char);

char *pig(char *word)
{
    /* Check for a vowel*/
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};

    int isVowel = contains(vowels, *word);

    /* If it is a vowel 'way' is added to end */
    if(isVowel == 0)
    {
        /* Allocates memory based on the size of the addition */
        char *newWord = (char *)malloc((strlen(word) + 3)*sizeof(char));
        /* To add to the end of the string */
        char addition[] = {'w', 'a', 'y'};
        /* New string created */
        memcpy(newWord, word, strlen(word) * sizeof(char));
        memcpy(newWord + strlen(word), addition, 3 * sizeof(char));

        return newWord;
    }
    /* If it is a constonant, moves constonants to end
    and adds 'ay' */
    else
    {
        
        /* Get a list of all initial constonants*/
        /* Allocates the max possible memory for constonants */
        char *constonants = (char *)malloc(strlen(word)*sizeof(char));
        int n = 0;
        while(isVowel == 1)
        {
            *constonants = *word;
            word++;
            /* For checking if y is the first letter */
            if(*constonants == 'y')
            {
                isVowel = 0;
            }
            else
            {
                constonants++;
                n++;
                /* Checks if the next letter is a vowel */
                isVowel = contains(vowels, *word);

                /* Checks if the next letter is y */
                if( *word == 'y')
                    isVowel = 0;
            }
        }
        /* roll back constonants */
        while(n > 0)
        {
            constonants--;
            n--;
        }
        /* Reallocates based upon string size */
        constonants = realloc(constonants, strlen(constonants) + 1);
        /* Allocates memory based on the size of the addition */
        char *newWord = (char *)malloc((strlen(word) + 2)*sizeof(char));
        /* To add to the end of the string */
        char addition[] = {'a', 'y'};
        /* combine */
        memcpy(newWord, word, strlen(word) * sizeof(char));
        memcpy(newWord + strlen(word), constonants, (strlen(constonants)) * sizeof(char));
        memcpy(newWord + (strlen(word) + strlen(constonants)), addition, 2 * sizeof(char));

        free(constonants);
        return newWord;
    }
}

int contains(char *letters, char toCheck)
{
    /* Checks if character is in list of
    chars, used to check for vowels */
    int i;
    for(i=0; i<5; i++)
    {
        if(*letters == toCheck)
        {
            return 0;
        }
        letters++;
    }
    return 1;
}