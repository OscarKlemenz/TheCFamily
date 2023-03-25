#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "riffle.h"

void riffle_once(void* L, int len, int size, void* work) 
{
    // Sets the seed for random
    srand(time(NULL));
    /* Initialising the A and B deck */
    int midpoint = len / 2;
    char* A = (char*)L;
    char* B = A + midpoint * size;
    /* Counters to check when end of A and B are reached */
    int Aindex = 0;
    int Bindex = midpoint;

    while (Aindex < midpoint && Bindex < len) {
        /* Randomly picks between A and B */
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
    /* Populates work with remainder of cards */
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
    work = (char*)work - len * size;
    /* Populates L with the new cards */
    for (int i = 0; i < len; i++) {
        memcpy(L, work, size);
        L = (char*)L + size;
        work = (char*)work + size;
    }
    L = (char*)L - len * size;
}


void riffle(void *L, int len, int size, int N)
{
    // Create a work array of the same size
    int *work = (int *)malloc(len * size);
    if (work == NULL) {
        // Failed to allocate memory, return failure, PLACE SOME ERROR CJHECKING HERE
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
    if (L == NULL || len < 2 || size < 1 || cmp == NULL) {
        return 0; // Invalid input, return failure
    }

    char *work = malloc(len * size); // Allocate temporary buffer for riffle
    if (work == NULL) {
        return 0; // Failed to allocate memory, return failure
    }

    char *original = malloc(len * size);
    if (original == NULL)
    {
        return 0; // Failed to allocate memory, return failure
    }

    // Copy the original array for comparison
    memcpy(original, L, len * size);
    // Perform the riffle shuffle once
    riffle_once(L, len, size, work);
    // Check that all elements from the original array are in the shuffled array
    for (int i = 0; i < len; i++) {
        void *elem = L + i * size;
        int found = 0;
        for (int j = 0; j < len; j++) {
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
    for (int i = 0; i < len; i++) {
        void *elem = original + i * size;
        int found = 0;
        for (int j = 0; j < len; j++) {
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

// Compare two integers pointed to by void pointers
int cmp_int(void *a, void *b) {
    // Cast the values
    int x = *(int *)a;
    int y = *(int *)b;
    return x > y ? 1 : (x < y ? -1 : 0);
}

// Compare two strings pointed to by void pointers
int cmp_str(void *a, void *b) {
    char *x = *(char **)a;
    char *y = *(char **)b;
    // If equal will return a 0, if not returns a 1
    return strcmp(x, y);
}

float quality(int *numbers, int len)
{
    // Check if each number is greater than the previous one
    int total = 0;
    int comparisons = (len - 1);
    int i;
    for(i=0;i<comparisons;i++)
    {
        int prev = *numbers;
        numbers++;
        int curr = *numbers;
        // For each that is greater than previous
        if(prev < curr)
        {
            total++;
        }
    }
    // Quality is then total / comparisons
    return ((float)total / (float)comparisons);
    
}

float average_quality(int N, int shuffles, int trials)
{
    int *nums = malloc(N * sizeof(int));
    float qual_total = 0;
    
    // For num of trials 
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
