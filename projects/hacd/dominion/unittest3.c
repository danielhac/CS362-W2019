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
    int numPlayer = 2;
    int countErrors = 0;
    int typeCards = 10;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    printf("Starting Test 3 -- kingdomCards()\n");
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);

    int* kingdomCardsTemp = kingdomCards(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    int i;
    for(i = 0; i < typeCards ; i++) {
        if(kingdomCardsTemp[i] != i + 1) {
            printf("Failed -- Kingdom Card# %d\n", kingdomCardsTemp[i]);
            countErrors++;
        }
    }

    if (countErrors == 0)
        printf("Successfully passed all tests for Test 3!\n");

    return 0;
}
