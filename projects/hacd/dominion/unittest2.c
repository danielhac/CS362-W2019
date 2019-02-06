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
    int typeCards = 27;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int cards[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens,
                 mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse,
                 embargo, outpost, salvager, sea_hag, treasure_map};
    char* cardName[27] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", "feast", "gardens",
                 "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute", "ambassador", "cutpurse",
                 "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};

    printf("Starting Test 2 -- getCost()\n");
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);

    int i;
    for(i = 0; i < typeCards ; i++) {
        if(getCost(cards[i]) < 0 && getCost(cards[i]) > 8) {
            printf("Failed -- Card: %s\n", cardName[i]);
            countErrors++;
        }
    }

    if (countErrors == 0)
        printf("Successfully passed all tests for Test 2!\n");

    return 0;
}
