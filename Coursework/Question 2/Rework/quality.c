#include <stdio.h>
#include "riffle.h"

int main()
{
    printf("Testing avg quality\n");

    float qual = average_quality(50, 10, 30);

    printf("%f\n", qual);

    return 0;
}