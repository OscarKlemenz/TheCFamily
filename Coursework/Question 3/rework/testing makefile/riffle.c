/* Program: riffle.c
 *  --------------
 *  riffle.c is the main driver for shuffling a list of
 *  elements
 * 
 *  Author: Oscar Klemenz
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "riffle.h"

void riffle_once(void* L, int len, int size, void* work) 
{
    /* Procedure: riffle_once
     * ----------------------
     * Performs a single riffle shuffle on list L  
     *
     * L: List to be shuffled
     * len: Length of list L
     * size: Size of each item in list L
     * work: Auxillary array to perform work while shuffling
    */

    // Initialising the A and B deck
    int midpoint = len / 2;
    char* A = (char*)L;
    char* B = A + midpoint * size;
    // Counters to check when end of A and B are reached
    int Aindex = 0;
    int Bindex = midpoint;

    while (Aindex < midpoint && Bindex < len) {
        // Randomly picks between A and B 
        if (rand() % 2 == 0) {
            memcpy(work, A, size);
            A += size;
            Aindex++;
        }
        else {
            memcpy(work, B, size);
            B += size;
            Bindex++;
        }
        work = (char*)work + size;
    }
    // Populates work with remainder of cards
    while (Aindex < midpoint) {
        memcpy(work, A, size);
        A += size;
        Aindex++;
        work = (char*)work + size;
    }
    while (Bindex < len) {
        memcpy(work, B, size);
        B += size;
        Bindex++;
        work = (char*)work + size;
    }
    // Returns to the start of work
    work = (char*)work - len * size;
    // Populates L with the new cards
    for (int i = 0; i < len; i++) {
        memcpy(L, work, size);
        L = (char*)L + size;
        work = (char*)work + size;
    }
    L = (char*)L - len * size;
}


void riffle(void *L, int len, int size, int N)
{
    /* Procedure: riffle
     * -----------------
     * Using riffle_once, performs N riffle shuffles on list L
     * 
     * L: List to be shuffled
     * len: Length of list L
     * size: Size of each item in list L
     * N: number of times riffle_once is called
    */
    // Create a work array of the same size
    int *work = (int *)malloc(len * size);
    if (work == NULL) {
        // Failed to allocate memory, return failure
        printf("Error! Could not allocate memory\n");
        exit(-1);
    }

    int i;
    for(i=0;i<N;i++)
    {
        riffle_once(L, len, size, work);
    }
    
    free(work);
}

int check_shuffle(void *L, int len, int size, int (* cmp)(void *, void *))
{
    /* Function: check_shuffle
     * -----------------------
     * Checks that all the elements in list L are still contained in L
     * after a riffle shuffle is performed.
     * 
     * L: List to be shuffled
     * len: Length of list L
     * size: Size of each item in list L
     * cmp: Function to check each element is still contained in the list
     * 
     * Returns: 1 if all elements are still there, 0 if not
    */
    if (L == NULL || len < 2 || size < 1 || cmp == NULL) {
        // Invalid input, return failure
        printf("Error! Invalid input\n");
        exit(-1);
    }
    // Allocate temporary buffer for riffle
    char *work = malloc(len * size);
    if (work == NULL) {
        // Failed to allocate memory, return failure
        printf("Error! Could not allocate memory\n");
        exit(-1);
    }

    char *original = malloc(len * size);
    if (original == NULL)
    {
        // Failed to allocate memory, return failure
        printf("Error! Could not allocate memory\n");
        exit(-1);
    }

    // Copy the original array for comparison
    memcpy(original, L, len * size);
    // Perform the riffle shuffle once
    riffle_once(L, len, size, work);
    // Check that all elements from the original array are in the shuffled array
    int i;
    int j;
    for (i = 0; i < len; i++) {
        void *elem = L + i * size;
        int found = 0;
        for (j = 0; j < len; j++) {
            if (cmp(elem, original + j * size) == 0) {
                found = 1;
                break;
            }
        }
        // If not returns 0
        if(!found)
        {
            return 0;
        }
    }
    // Check that all elements in the shuffled array are in the original array
    for (i = 0; i < len; i++) {
        void *elem = original + i * size;
        int found = 0;
        for (j = 0; j < len; j++) {
            if (cmp(elem, L + j * size) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            return 0;
        }
    }

    // Frees memory
    free(work);
    free(original);

    // Resets the array, as this is only for testing ordering
    memcpy(L, original, len * size);

    // Both checks have passed so return 1
    return 1;
}

int cmp_int(void *a, void *b) {
    /* Function: cmp_int
     * -----------------
     * Compares two integers
     * 
     * a, b: Integers to be compared
     * 
     * Returns:  -1 if a > b, 0 if a = b, and 1 if a < b
    */
    int x = *(int *)a;
    int y = *(int *)b;
    return x > y ? -1 : (x < y ? 1 : 0);
}


int cmp_str(void *a, void *b) {
    /* Function: cmp_str
     * -----------------
     * Compares two chars
     * 
     * a, b: Chars to be compared
     * 
     * Returns: If equal will return a 0, if not returns a 1
    */
    char *x = *(char **)a;
    char *y = *(char **)b;
    return strcmp(x, y);
}

float quality(int *numbers, int len)
{
    /* Function: quality
     * -----------------
     * - Checks the quality of a list of ints
     * - Quality is checked by if an element is less than the next one
     * - Quality will be smaller when less are in order
     * 
     * numbers: List of numbers to check
     * len: Length of list
     * 
     * Returns: Float value representing the quality of shuffle
    */
    int total = 0;
    int comparisons = (len - 1);
    int i;
    for(i=0;i<comparisons;i++)
    {
        int prev = *numbers;
        numbers++;
        if(prev < *numbers)
            total++;
    }
    // Quality is total / comparisons
    return ((float)total / (float)comparisons);
    
}

float average_quality(int N, int shuffles, int trials)
{
    /* Function: average_quality
     * -------------------------
     * Calculates the average quality of an array of length N
     * over a number of trials, with each trial having a specified
     * amount of shuffles
     * 
     * N: Length of list of nums
     * shuffles: How many times to shuffle on each trial
     * trials: How many trials to perform to get the average
     * 
     * Returns: Float value representing the average quality from the trials
     *    
    */
    int *nums = malloc(N * sizeof(int));
    if (nums == NULL) {
        // Failed to allocate memory, return failure
        printf("Error! Could not allocate memory\n");
        exit(-1);
    }
    float qual_total = 0;
    
    int i;
    for(i=0;i<trials;i++)
    {
        // Generate an array of numbers from 0 to N-1
        int i;
        for(i=0;i<N;i++)
        {
            *nums = i;
            nums++;
        }
        nums -= N;
        // Riffles for shuffles times
        riffle(nums, N, sizeof(int), shuffles);
        // Add quality to running total
        qual_total += quality(nums, N);
    }
    free(nums);
    // Divide by number of trials    
    float avg_qual = qual_total / (float)trials;
    // Return average
    return avg_qual;
}
