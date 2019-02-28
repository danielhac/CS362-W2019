/*****************************************************************************************************************************
* isGameOver
The game ends at the end of any player's turn in which at least one of the following is true:
  " The Province Supply pile is empty (or the Colony Supply pile is empty, in a game with the Colony card from the 
        Prosperity expansion)
    Any three Supply piles are empty. (Any four piles when playing with five or six players.) This includes all the Supply 
        piles, not just the 10 Kingdom card piles that are selected for each game. So, for instance, if the Estate pile, the 
        Curse pile, and one of the Kingdom card piles is empty, the game ends.
  ..."
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
* isGameOver::provinceTesting
*/
  char* testName = "isGameOver::provinceTesting::lowProvinceSupply";
  state->supplyCount[province] = 1;
  if(isGameOver(state))
    result = 0;
  assertTrue(result, &overallResult, testName, 0);

  testName = "isGameOver::provinceTesting::fullProvinceSupply";
  resetResult(&result);
  state->supplyCount[province] = 8;
  if(isGameOver(state))
    result = 0;
  assertTrue(result, &overallResult, testName, 0);

  testName = "isGameOver::provinceTesting::noProvinceSupply";
  resetResult(&result);
  state->supplyCount[province] = 0;
  if(! isGameOver(state))
    result = 0;
  assertTrue(result, &overallResult, testName, 0);

/*
* isGameOver::supplyTesting
*/
  state->supplyCount[province] = 8;

  testName = "isGameOver::supplyTesting::gameOver";
  resetResult(&result);
  state->supplyCount[0] = 0;
  state->supplyCount[13] = 0;
  state->supplyCount[24] = 0;
  if(! isGameOver(state))
    result = 0;
  assertTrue(result, &overallResult, testName, 0);

  testName = "isGameOver::supplyTesting::gameNotOver";
  resetResult(&result);
  state->supplyCount[0] = 1;
  if(isGameOver(state))
    result = 0;
  assertTrue(result, &overallResult, testName, 0);

  testName = "isGameOver::OVERALL";
  assertTrue(result, &overallResult, testName, 1);

  return 0;
}