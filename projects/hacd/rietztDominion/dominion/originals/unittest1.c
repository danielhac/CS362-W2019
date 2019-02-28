/*****************************************************************************************************************************
* fullDeckCount()
*****************************************************************************************************************************/

#include "../dominion.h"
#include "../dominion_helpers.h"
#include "../rngs.h"
#include "../testHelpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void setTestInputs(int testCard, int otherCard, struct gameState* state){
  
  for(int p=0; p < state->numPlayers; p++){
    //artificially set hand, deck, and discard counts
    state->handCount[p] = 5;
    state->deckCount[p] = 5;
    state->discardCount[p] = 5;

    //set hand cards
    for(int i=0; i < state->handCount[p]; i++){
      if(p == 0){
        state->hand[p][i] = testCard;                           //player 1 hand has all adventurer
      } else if(p == 1 && i == state->handCount[p] / 2){  
        state->hand[p][i] = testCard;                           //player 2 hand has 1 adventurer
      } else {
        state->hand[p][i] = otherCard;                          //player 3 hand has 0 adventurer
      }
    }

    //set deck cards
    for(int i=0; i < state->deckCount[p]; i++){
      if(p == 0){
        state->deck[p][i] = testCard;                           //player 1 deck has all adventurer
      } else if(p == 1 && i == state->deckCount[p] / 2){  
        state->deck[p][i] = testCard;                           //player 2 deck has 1 adventurer
      } else {
        state->deck[p][i] = otherCard;                          //player 3 deck has 0 adventurer
      }
    }

    //set deck cards
    for(int i=0; i < state->discardCount[p]; i++){
      if(p == 0){
        state->discard[p][i] = testCard;                        //player 1 discard has all adventurer
      } else if(p == 1 && i == state->discardCount[p] / 2){  
        state->discard[p][i] = testCard;                        //player 2 discard has 1 adventurer
      } else {
        state->discard[p][i] = otherCard;                       //player 3 discard has 0 adventurer
      }
    }
  }
}


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
* fullDeckCount::state->numPlayers
*/
  char* testName = "fullDeckCount::state->numPlayers";
  if(state->numPlayers != players){
    result = 0;
  }
  assertTrue(result, &overallResult, testName, 0);  

/*
* fullDeckCount::correctResult
*/
  testName = "fullDeckCount::correctResult";
  resetResult(&result);
  int testCard = adventurer;
  setTestInputs(testCard, smithy, state);
  for(int p=0; p < state->numPlayers; p++){
    if( p==0 && fullDeckCount(p, testCard, state) != (state->handCount[p] + state->deckCount[p] + state->discardCount[p]) ){
      result = 0;
    } else if( p==1 && fullDeckCount(p, testCard, state) != 3){
      result = 0;
    } else if( p>1 && fullDeckCount(p, testCard, state) != 0){
      result = 0;
    }
    overallResult = result;
  }
  assertTrue(result, &overallResult, testName, 0);

  testName = "fullDeckCount::OVERALL";
  assertTrue(result, &overallResult, testName, 1);

  return 0;
}