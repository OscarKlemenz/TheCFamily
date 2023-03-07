#include <stdio.h>
#include "riffle.h"

int main()
{
    /* Sets the seed for random*/
    srand(time(NULL));
    /* Create an array to test */
    char *greek[] = {"alpha", "beta", "gamma", "delta", "epsilon", "zeta", 
    "eta", "theta", "iota", "kappa", "lambda", "mu"};

    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    /* Create size, which is the number of bytes each element is */
    int size = sizeof(*nums);

    /* Make a list of pointers */
    int length = sizeof(nums) / size;

    riffle(nums, length, size, 5);

    int i;
    for(i=0;i<length;i++)
    {
        printf("%d\n", nums[i]);
    }

    return 0;
}