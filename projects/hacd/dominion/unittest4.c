/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main() {
    struct gameState G;
    int seed = 1000;
    int numPlayer = 4;
    int countErrors = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    printf("Starting Test 4 -- endTurn()\n");
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);

    int i;
    for(i = 0; i < G.numPlayers ; i++) {
        if(whoseTurn(&G) != i) {
            printf("Failed -- Player# %d out of turn\n", whoseTurn(&G));
            countErrors++;
        }
        endTurn(&G);
    }

    if (countErrors == 0)
        printf("Successfully passed all tests for Test 4!\n");

    return 0;
}
