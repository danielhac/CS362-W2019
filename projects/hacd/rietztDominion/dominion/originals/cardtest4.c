/*****************************************************************************************************************************
* village
*****************************************************************************************************************************/

#include "../dominion.h"
#include "../dominion_helpers.h"
#include "../rngs.h"
#include "../testHelpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main() {

  int seed = 1000;
  int players = 4;
  int result = 1;
  int overallResult = 1;
  int handPos = 2;
  int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
  
  struct gameState* state = newGame();
  newTestInstance(players, kingdomCards, seed, state);
  int player = whoseTurn(state);

  state->hand[player][handPos] = village;

/*
* village::addsCard
*/
  char* testName = "village::addsCard";
  int initialHandCount = state->handCount[player];
  cardEffect(village, 0, 0, 0, state, handPos, 0);
  if(state->handCount[player] != initialHandCount){
    result = 0;
  }
  assertTrue(result, &overallResult, testName, 0);

/*
* village::adds2Actions
*/
  testName = "village::adds2Actions";
  int initialActionCount = state->numActions;
  cardEffect(village, 0, 0, 0, state, handPos, 0);
  if(state->numActions != initialActionCount + 2){
    result = 0;
  }
  assertTrue(result, &overallResult, testName, 0);

  testName = "village::OVERALL";
  assertTrue(result, &overallResult, testName, 1);

  return 0;
}
/*
void villageEffect(int currentPlayer, int handPos, struct gameState* state){
  //+1 Card
  drawCard(currentPlayer, state);
  
  //+2 Actions
  state->numActions = state->numActions + 2;
  
  //discard played card from hand
  discardCard(handPos, currentPlayer, state, 0);
  return 0;
}
*/
