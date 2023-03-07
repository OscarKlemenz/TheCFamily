#include <stdio.h>
#include "riffle.h"

int main()
{
    // Integer test array
    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    // Create size, which is the number of bytes each element is
    int size = sizeof(*nums);
    // Make a list of pointers 
    int length = sizeof(nums) / size;

    printf("Before shuffle: \n");
    int i;
    for(i=0;i<length;i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");

    riffle(nums, length, size, 5);

    printf("After shuffle: \n");
    for(i=0;i<length;i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");

    // Checks the shuffle
    printf("Checking shuffle...\n");
    int pass = check_shuffle(nums, length, size, cmp_int);
    if(pass)
        printf("Shuffle passed!\n");
    else
        printf("Shuffle failed!\n");

    // String test array
    char *greek[] = {"alpha", "beta", "gamma", "delta", "epsilon", "zeta", 
    "eta", "theta", "iota", "kappa", "lambda", "mu"};

    // Create size, which is the number of bytes each element is 
    size = sizeof(*greek);
    // Make a list of pointers 
    length = sizeof(greek) / size;

    printf("Before shuffle: \n");
    for(i=0;i<length;i++)
    {
        printf("%s ", greek[i]);
    }
    printf("\n");

    riffle(greek, length, size, 5);

    printf("After shuffle: \n");
    for(i=0;i<length;i++)
    {
        printf("%s ", greek[i]);
    }
    printf("\n");

    // Checks the shuffle
    printf("Checking shuffle...\n");
    pass = check_shuffle(greek, length, size, cmp_str);
    if(pass)
        printf("Shuffle passed!\n");
    else
        printf("Shuffle failed!\n");

    return 0;
}