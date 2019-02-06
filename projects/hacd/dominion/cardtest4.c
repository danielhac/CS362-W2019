#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "great_hall"
int errorCount = 0;

void newAssert(int bool, char* errorMsg) {
    if(!bool) {
        printf("%s\n", errorMsg);
		errorCount++;
    }
}

void stateAssert(struct gameState *prevG, struct gameState *tempG, int player) {
	if(prevG->deckCount[player] != tempG->deckCount[player]) {
		printf("Failed -- Other player's deck changed\n");
		errorCount++;
	}
	if(prevG->handCount[player] != tempG->handCount[player]) {
		printf("Failed -- Other player's hand count changed \n");
		errorCount++;
	}
}

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
	int numActions = 0;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int nextPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	printf("TEST 1: Before running %s\n", TESTCARD);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
    discarded = 0;

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	printf("numActions = %d, expected = %d\n", testG.numActions, G.numActions);
	newAssert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, "Failed -- hand count != expected");
	newAssert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, "Failed -- deck count != expected");
	newAssert(testG.coins == G.coins + xtraCoins, "Failed -- coins != expected");
	newAssert(testG.numActions == G.numActions, "Failed -- numActions != expected");

	printf("TEST 2: After running %s\n", TESTCARD);
	cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);

    discarded = 1;
	newCards = 1;
	numActions = 1;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	printf("numActions = %d, expected = %d\n", testG.numActions, G.numActions);
	newAssert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, "Failed -- hand count != expected");
	newAssert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, "Failed -- deck count != expected");
	newAssert(testG.coins == G.coins + xtraCoins, "Failed -- coins != expected");
	newAssert(testG.numActions == G.numActions, "Failed -- numActions != expected");
    stateAssert(&G, &testG, nextPlayer);

	if(errorCount == 0) {
		printf("TEST SUCCESSFULLY COMPLETED WITHOUT ERRORS FOR: %s\n", TESTCARD);
	}

	return 0;
}


