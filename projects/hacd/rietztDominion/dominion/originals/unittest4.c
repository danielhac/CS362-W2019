/*****************************************************************************************************************************
* updateCoins
*****************************************************************************************************************************/


#include "../dominion.h"
#include "../dominion_helpers.h"
#include "../rngs.h"
#include "../testHelpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void setTestInput1(int players, int handSize, struct gameState* state){
  for(int p=0; p < players; p++){
    state->handCount[p] = handSize;
    for(int i=0; i < state->handCount[p]; i++){
      switch (p){
        case 0:                                     //all gold
          state->hand[p][i] = gold; 
          break;
        case 1:                                     //all silver
          state->hand[p][i] = silver;
          break;
        case 2:                                     //all copper
          state->hand[p][i] = copper;
          break;
        case 3:                                     //all 3 evenly distributed
          if(i%3 == 0)
            state->hand[p][i] = gold;
          if(i%3 == 1)
            state->hand[p][i] = silver;
          if(i%3 == 2)
            state->hand[p][i] = copper;
          break;
      }
    }
  }
}

void setTestInput2(int players, int handSize, struct gameState* state){
  for(int p=0; p < players; p++){
    state->handCount[p] = handSize;
    for(int i=0; i < state->handCount[p]; i++){
      switch (p){
        case 0:                                     //no coins
          state->hand[p][i] = smithy;
          break;
        case 1:                                     //half gold, half not coins
          if(i%2 == 0)
            state->hand[p][i] = smithy;
          if(i%2 == 1)
            state->hand[p][i] = gold;
          break;
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
  setTestInput1(players, MAX_HAND, state);


/*
* updateCoins::allGold
*/
  char* testName = "updateCoins::allGold";
  updateCoins(0, state, 0);
  if( state->coins != MAX_HAND * 3 )
    result = 0;
  assertTrue(result, &overallResult, testName, 0);

/*
* updateCoins::allSilver
*/
  testName = "updateCoins::allSilver";
  resetResult(&result);
  updateCoins(1, state, 0);
  if( state->coins != MAX_HAND * 2 )
    result = 0;
  assertTrue(result, &overallResult, testName, 0);

/*
* updateCoins::allCopper
*/
  testName = "updateCoins::allCopper";
  resetResult(&result);
  updateCoins(2, state, 0);
  if( state->coins != MAX_HAND )
    result = 0;
  assertTrue(result, &overallResult, testName, 0);

/*
* updateCoins::allEvenlyDistributed
*/
  setTestInput1(players, 300, state);
  testName = "updateCoins::allEvenlyDistributed";
  resetResult(&result);
  updateCoins(3, state, 0);
  if( state->coins != 600 )
    result = 0;
  assertTrue(result, &overallResult, testName, 0);


  setTestInput2(players, MAX_HAND, state);
/*
* updateCoins::noCoins
*/
  testName = "updateCoins::noCoins";
  resetResult(&result);
  updateCoins(0, state, 0);
  if( state->coins != 0 )
    result = 0;
  assertTrue(result, &overallResult, testName, 0);

/*
* updateCoins::halfGold
*/
  testName = "updateCoins::halfGold";
  resetResult(&result);
  updateCoins(1, state, 0);
  if( state->coins != (MAX_HAND/2) * 3 )
    result = 0;
  assertTrue(result, &overallResult, testName, 0);

  testName = "updateCoins::OVERALL";
  assertTrue(result, &overallResult, testName, 1);

  return 0;
}


/*
int updateCoins(int player, struct gameState *state, int bonus){
  int i;
	
  //reset coin count
  state->coins = 0;

  //add coins for each Treasure card in player's hand
  for (i = 0; i < state->handCount[player]; i++){
    if (state->hand[player][i] == copper){
      state->coins += 1;
    } else if (state->hand[player][i] == silver){
      state->coins += 2;
    } else if (state->hand[player][i] == gold){
        state->coins += 3;
    }	
  }	

  //add bonus
  state->coins += bonus;

  return 0;
}
*/