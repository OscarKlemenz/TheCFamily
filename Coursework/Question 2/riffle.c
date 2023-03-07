#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void riffle_once(void *,int, int, void *);
void riffle(void *,int, int, int);

void riffle_once(void* L, int len, int size, void* work) 
{
    /* Initialising the A and B deck */
    int midpoint = len / 2;
    int* A = (int*)L;
    int* B = A + midpoint;
    /* Counters to check when end of A and B are reached */
    int Aindex = 0;
    int Bindex = midpoint;

    while (Aindex < midpoint && Bindex < len) {
        /* Randomly picks between A and B */
        if (rand() % 2 == 0) {
            *(int*)work = *A;
            A++;
            Aindex++;
        }
        else {
            *(int*)work = *B;
            B++;
            Bindex++;
        }
        work = (int*)work + 1;
    }
    /* Populates work with remainder of cards */
    while (Aindex < midpoint) {
        *(int*)work = *A;
        A++;
        Aindex++;
        work = (int*)work + 1;
    }
    while (Bindex < len) {
        *(int*)work = *B;
        B++;
        Bindex++;
        work = (int*)work + 1;
    }
    work = (int*)work - len;
    /* Populates L with the new cards */
    for (int i = 0; i < len; i++) {
        *(int*)L = *(int*)work;
        L = (int*)L + 1;
        work = (int*)work + 1;
    }
    L = (int*)L - len;
}

void riffle(void *L, int len, int size, int N)
{
    /* Create a work array of the same size */
    int *work = (int *)malloc(len * sizeof(int));
    
    int i;
    for(i=0;i<N;i++)
    {
        riffle_once(L, len, size, work);
    }
    
    free(work);
}

/*
    void riffle_once(void *L, int size, void *work)
{

    int midpoint = size / 2;
    void *A = L;
    void *B = L + midpoint;

    int Aindex = 0;
    int Bindex = midpoint;


    while((Aindex < midpoint) && (Bindex < size))
    {

        int random_num = rand() % 2;
        if(random_num == 0)
        {
            *work = *A;
            A++;
            Aindex++;
        }
        else
        {
            *work = *B;
            B++;
            Bindex++;
        }
        work++;
    }

    while(Aindex < midpoint)
    {
        *work = *A;
        A++;
        Aindex++;
        work++;
    }
    while(Bindex < size)
    {
        *work = *B;
        B++;
        Bindex++;
        work++;
    }
    work -= size;


    int i;
    for(i=0;i<size;i++)
    {
        *L = *work;
        L++;
        work++;
    }

    L -= size;

*/