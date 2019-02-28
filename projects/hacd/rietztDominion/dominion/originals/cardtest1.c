/*****************************************************************************************************************************
* smithy
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

  state->hand[player][handPos] = smithy;

/*
* smithy::adds3Cards::nonEdge
*/
  int initialHandCount = state->handCount[player];
  char* testName = "smithy::adds3Cards::nonEdge";
  cardEffect(smithy, 0, 0, 0, state, handPos, 0);
  if(state->handCount[player] != initialHandCount + 2){
    result = 0;
  }
  assertTrue(result, &overallResult, testName, 0);

/*
* smithy::discarded::nonEdge
*/
  testName = "smithy::discarded::nonEdge";
  resetResult(&result);
  cardEffect(smithy, 0, 0, 0, state, handPos, 0);
  if(state->hand[player][handPos] == smithy){
    result = 0;
  }
  assertTrue(result, &overallResult, testName, 0);

/*
* smithy::adds3Cards::maxEdge
*/
  testName = "smithy::adds3Cards::maxEdge";
  resetResult(&result);
  initialHandCount = state->handCount[player];
  state->hand[player][state->handCount[player]-1] = smithy;
  cardEffect(smithy, 0, 0, 0, state, handPos, 0);
  if(state->handCount[player] != initialHandCount + 2){
    result = 0;
  }
  assertTrue(result, &overallResult, testName, 0);

/*
* smithy::discarded::maxEdge
*/
  testName = "smithy::discarded::maxEdge";
  resetResult(&result);
  cardEffect(smithy, 0, 0, 0, state, handPos, 0);
  if(state->hand[player][state->handCount[player]-1] == smithy){
    result = 0;
  }
  assertTrue(result, &overallResult, testName, 0);

/*
* smithy::adds3Cards::minEdge
*/
  testName = "smithy::adds3Cards::minEdge";
  resetResult(&result);
  initialHandCount = state->handCount[player];
  state->hand[player][0] = smithy;
  cardEffect(smithy, 0, 0, 0, state, handPos, 0);
  if(state->handCount[player] != initialHandCount + 2){
    result = 0;
  }
  assertTrue(result, &overallResult, testName, 0);

/*
* smithy::discarded::minEdge
*/
  testName = "smithy::discarded::minEdge";
  resetResult(&result);
  cardEffect(smithy, 0, 0, 0, state, handPos, 0);
  if(state->hand[player][handPos] == smithy){
    result = 0;
  }
  assertTrue(result, &overallResult, testName, 0);

  testName = "smithy::OVERALL";
  assertTrue(result, &overallResult, testName, 1);

  return 0;
}


/*
void smithyEffect(int currentPlayer, int handPos, struct gameState *state){
  //+3 Cards
  for (int i = 0; i <= 3; i++){             //BUG: should be 'i < 3'
    drawCard(currentPlayer, state);
  }
}
*/