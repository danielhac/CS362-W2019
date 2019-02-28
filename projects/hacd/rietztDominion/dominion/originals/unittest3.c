/*****************************************************************************************************************************
* handCard
*****************************************************************************************************************************/


#include "../dominion.h"
#include "../dominion_helpers.h"
#include "../rngs.h"
#include "../testHelpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


/*****************************************************************************************************************************/


int main() {

  int seed = 1000;
  int players = 4;
  int result = 1;
  int overallResult = 1;
  int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
  
  struct gameState* state = newGame();
  newTestInstance(players, kingdomCards, seed, state);

/*
* handCard::accessible::maxEdge
*/
  char* testName = "handCard::accessible::maxEdge";
  if(! handCard(MAX_HAND, state)){
    result = 0;
  }
  assertTrue(result, &overallResult, testName, 0);

/*
* handCard::accessible::minEdge
*/
  testName = "handCard::accessible::minEdge";
  resetResult(&result);
  if(! handCard(0, state)){
    result = 0;
  }
  assertTrue(result, &overallResult, testName, 0);

/*
* handCard::accessible::mid
*/
  testName = "handCard::accessible::mid";
  resetResult(&result);
  if(! handCard(250, state)){
    result = 0;
  }
  assertTrue(result, &overallResult, testName, 0);

/*
* handCard::correctResult
*/
  testName = "handCard::cardTest::correctResult";
  resetResult(&result);
  state->hand[0][0] = smithy;
  state->hand[0][5] = adventurer;
  if(handCard(0, state) != smithy || handCard(5, state) != adventurer){
    result = 0;
  }
  assertTrue(result, &overallResult, testName, 0);

  testName = "handCard::OVERALL";
  assertTrue(result, &overallResult, testName, 1);

  return 0;
}