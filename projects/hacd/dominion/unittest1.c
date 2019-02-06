#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main() {
    struct gameState G;
    int seed = 1000;
    int numPlayer = 2;
    int countErrors = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    printf("Starting Test 1 -- numHandCards()\n");
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);

    int i, j;
    for(i = 0; i < G.numPlayers ; i++) {
        G.whoseTurn = i;
        for (j = 0; j < MAX_HAND; j++) {
            G.handCount[i] = j;
            if (numHandCards(&G) != j) {
                printf("Failed -- Card: %d | Player: %d\n", j, i+1);
                countErrors++;
            }
        }
    }

    if (countErrors == 0)
        printf("Successfully passed all tests for Test 1!\n");

    return 0;
}
