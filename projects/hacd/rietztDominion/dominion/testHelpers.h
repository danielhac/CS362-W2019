#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void newTestInstance(int players, int kingdomCards[10], int seed, struct gameState* state);

void assertTrue(int result, int* overallResult, char* testName, int isOverall);

void resetResult(int* result);

int isTreasure(int card);
int getTreasure(int player, struct gameState* state);
int getTreasureVal(int player, struct gameState* state);