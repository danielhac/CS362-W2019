#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "great_hall"
#define TESTRUNS 100
#define TESTSIZE (TESTRUNS * MAX_DECK * MAX_PLAYERS * 10)
#define MAXCARDS 29

double randNums[TESTRUNS * MAX_DECK * MAX_PLAYERS * 10];
int pos = 0;
int errorCount = 0;

void newAssert(int bool, char *errorMsg) {
    if (!bool) {
        printf("%s\n", errorMsg);
        errorCount++;
    }
}

void stateAssert(struct gameState *prevG, struct gameState *tempG, int player) {
    if (prevG->deckCount[player] != tempG->deckCount[player]) {
        printf("Failed -- Other player's deck changed\n");
        errorCount++;
    }
    if (prevG->handCount[player] != tempG->handCount[player]) {
        printf("Failed -- Other player's hand count changed \n");
        errorCount++;
    }
}

void createRandNums() {
    int i;
    for (i = 0; i < TESTSIZE; i++) {
        randNums[i] = Random();
    }
}

int createRandInt(int max) {
    return (int) (max * randNums[pos++]);
}

int main() {
    srand((unsigned int) (time(NULL)));
    const int newCards = 1;
    int discarded = 1;
    const int xtraCoins = 0;
    int shuffledCards = 0;
    const int numActions = 1;
    int minHandCount = 5;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 3;
    int thisPlayer = 0;
    int nextPlayer = 1;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards

    createRandNums();

    int i;
    for (i = 0; i < TESTRUNS; i++) {
        printf("----------------- Test: %d, Card: %s ----------------\n", i, TESTCARD);
        numPlayers = createRandInt(numPlayers) + 2;
        initializeGame(numPlayers, k, seed, &G);

        int j, l, newDeckSize, newLargeHand;
        newDeckSize = createRandInt(MAX_DECK) + 1;

        for (j = 0; j < numPlayers; j++) {
            if (newDeckSize > minHandCount) {
                if (Random() < .95) {
                    G.handCount[j] = minHandCount;
                } else {
                    newLargeHand = (int) (minHandCount * 10 * Random());
                    G.handCount[j] = newLargeHand > newDeckSize ? newDeckSize : newLargeHand;
                }
            } else {
                G.handCount[j] = newDeckSize;
            }

            newDeckSize -= G.handCount[j];

            for (l = 0; l < G.handCount[j]; l++) {
                G.hand[j][l] = createRandInt(MAXCARDS);
            }
        }

        for (j = 0; j < numPlayers; j++) {
            G.deckCount[j] = createRandInt(newDeckSize);
            newDeckSize -= G.deckCount[j];

            for (l = 0; l < G.deckCount[j]; l++) {
                G.deck[j][l] = createRandInt(MAXCARDS);
            }
        }

        for (j = 0; j < numPlayers; j++) {
            G.discardCount[j] = newDeckSize;

            for (l = 0; l < G.discardCount[j]; l++) {
                G.discard[j][l] = createRandInt(MAXCARDS);
            }
        }

        if (handpos < G.handCount[j]) {
            G.hand[thisPlayer][handpos] = great_hall;
        } else {
            G.hand[thisPlayer][0] = great_hall;
        }

        memcpy(&testG, &G, sizeof(struct gameState));
        shuffledCards = 0;
        if (testG.deckCount[thisPlayer] < newCards)
            shuffledCards = testG.discardCount[thisPlayer];

        cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);

        newAssert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, "Failed -- hand count != expected");
        newAssert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, "Failed -- deck count != expected");
        newAssert(testG.coins == G.coins + xtraCoins, "Failed -- coins != expected");
        newAssert(testG.numActions == G.numActions + numActions, "Failed -- numActions != expected");
        if (shuffledCards) newAssert(testG.discardCount[thisPlayer] == 0, "Failed -- discard pile != expected");
        else newAssert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer], "Failed -- discard pile != expected");
        stateAssert(&G, &testG, nextPlayer);
    }

    return 0;
}