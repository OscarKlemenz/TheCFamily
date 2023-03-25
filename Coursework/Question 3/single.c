#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num_players>\n", argv[0]);
        exit(1);
    }

    int num_players = atoi(argv[1]);

    // TODO: Write your code here
    printf("Num players %d\n", num_players);

    return 0;
}