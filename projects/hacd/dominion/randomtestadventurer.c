#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "adventurer"
#define TESTRUNS 100
#define TESTSIZE (TESTRUNS * MAX_DECK * MAX_PLAYERS * 10)
#define MAXCARDS 32

double randNums[TESTRUNS * MAX_DECK * MAX_PLAYERS * 10];
int pos = 0;
int errorCount = 0;

struct newTreasure {
    int card;
    int position;
};

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
    const int newCards = 2;
    int discarded = 0;
    const int xtraCoins = 0;
    int shuffledCards = 0;
    const int numActions = 0;
    int minHandCount = 5;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 3;
    int thisPlayer = 0;
    int nextPlayer = thisPlayer + 1;
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

        int j, l, newDeckSize;
        newDeckSize = createRandInt(MAX_DECK) + 1;

        for (j = 0; j < numPlayers; j++) {
            if (newDeckSize > minHandCount) {
                if (Random() < .95) {
                    G.handCount[j] = minHandCount;
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
            G.hand[thisPlayer][handpos] = adventurer;
        } else {
            G.hand[thisPlayer][0] = adventurer;
        }

        memcpy(&testG, &G, sizeof(struct gameState));
        shuffledCards = 0;
        int treasureCount = 0, posCount = 0, last = 0;
        int origHandCount = testG.handCount[thisPlayer];
        struct newTreasure newTres[2];

        while (posCount < G.deckCount[thisPlayer] && treasureCount < 2) {
            for (last = G.deckCount[thisPlayer] - 1; -1 < last ; last--) {
                posCount++;
                if (G.deck[thisPlayer][last] == copper || G.deck[thisPlayer][last] ==  silver || G.deck[thisPlayer][last] ==  gold ) {
                    newTres[treasureCount].card = G.deck[thisPlayer][last];
                    newTres[treasureCount].position = posCount;
                    treasureCount++;
                }
                if (treasureCount == 2) break;
            }
        }

        while (posCount < (G.deckCount[thisPlayer] + G.discardCount[thisPlayer]) && treasureCount < 2) {
            for (last = G.discardCount[thisPlayer] -1 ; - 1 < last ; last--) {
                posCount++;
                if (G.discard[thisPlayer][last] == copper || G.discard[thisPlayer][last] ==  silver || G.discard[thisPlayer][last] ==  gold ) {
                    newTres[treasureCount].card = G.discard[thisPlayer][last];
                    newTres[treasureCount].position = posCount;
                    treasureCount++;
                }
                if (treasureCount == 2) break;
            }
        }

        if (G.deckCount[thisPlayer] < newCards)
            shuffledCards = G.discardCount[thisPlayer];

        cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

        newAssert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, "Failed -- hand count != expected");
        newAssert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, "Failed -- deck count != expected");
        newAssert(testG.hand[thisPlayer][origHandCount - 1] == newTres[1].card, "Failed -- treasure != expected");
        newAssert(testG.hand[thisPlayer][origHandCount - 2] == newTres[0].card, "Failed -- treasure != expected");
        newAssert(testG.coins == G.coins + xtraCoins, "Failed -- coins != expected");
        newAssert(testG.numActions == G.numActions + numActions, "Failed -- numActions != expected");
        if (shuffledCards) newAssert(testG.discardCount[thisPlayer] == 0, "Failed -- discard pile != expected");
        else newAssert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer], "Failed -- discard pile != expected");
        stateAssert(&G, &testG, nextPlayer);
    }

    return 0;
}