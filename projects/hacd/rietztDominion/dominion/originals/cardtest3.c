/*****************************************************************************************************************************
* cutPurse
*****************************************************************************************************************************/


#include "../dominion.h"
#include "../dominion_helpers.h"
#include "../rngs.h"
#include "../testHelpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void setTestInput(struct gameState* state){
  for(int p=0; p < state->numPlayers; p++){
    state->handCount[p] = 5;
    for(int i=0; i < state->handCount[p]; i++){
      if (p%2 == 0){
        state->hand[p][i] = copper;               //all copper
      } else {
        state->hand[p][i] = smithy;               //zero copper
      }
    }
  }
  state->hand[1][4] = copper;                     //one copper
}

int getCopperCount(int player, struct gameState* state){
  int count = 0;
  for(int i=0; i < state->handCount[player]; i++){
    if(state->hand[player][i] == copper)
      count++;
  }
  return count;
}


/*****************************************************************************************************************************/


int main() {

  int seed = 1000;
  int players = 4;
  int result = 1;
  int overallResult = 1;
  int handPos = 2;
  int initialTreasure = 0;
  int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
  
  struct gameState* state = newGame();
  newTestInstance(players, kingdomCards, seed, state);
  int player = whoseTurn(state);

  state->hand[player][handPos] = cutpurse;

/*
* cutpurse::addsTreasureVal2
*/
  char* testName = "cutpurse::adds2Coin";
  initialTreasure = state->coins;
  cardEffect(cutpurse, 0, 0, 0, state, handPos, 0);
  if(state->coins != initialTreasure + 2){
    result = 0;
  }
  assertTrue(result, &overallResult, testName, 0);

/*
* ccutpurse::copperCounts::correctResults
*/
  testName = "cutpurse::copperCounts::correctResults";
  resetResult(&result);
  setTestInput(state);
  cardEffect(cutpurse, 0, 0, 0, state, handPos, 0);
  if( getCopperCount(0, state) != 5 ||    //player1 doesn't have to discard any
      getCopperCount(2, state) != 4 ||    
      getCopperCount(1, state) != 0 ||    
      getCopperCount(3,state)!= 0) {
    result = 0;
  }
  assertTrue(result, &overallResult, testName, 0);

/*
* cutpurse::copperDiscard::correctResults
*/
  testName = "cutpurse::copperDiscard::correctResults";
  resetResult(&result);
  setTestInput(state);
  cardEffect(cutpurse, 0, 0, 0, state, handPos, 0);
  if( state->discardCount[2] != 1 || 
      state->discardCount[1] != 1 ||
      state->discardCount[3] != 0) {
        result = 0;
  }
  assertTrue(result, &overallResult, testName, 0);

  testName = "cutpurse::OVERALL";
  assertTrue(result, &overallResult, testName, 1);

  return 0;
}


/*
void cutPurseEffect(int currentPlayer, int handPos, struct gameState *state){
  updateCoins(currentPlayer, state, 2);
  for (int i = 0; i < state->numPlayers; i++){
    if (i != currentPlayer){
      for (int j = 0; j < state->handCount[i]; j++){
        if (state->hand[i][j] == copper){
          discardCard(j, i, state, 0);
          break;
        }
        else {     //BUG: should be 'if (j == state->handCount[i]) not 'else'
          for (int k = 0; k < state->handCount[i]; k++){
            if (DEBUG)
              printf("Player %d reveals card number %d\n", i, state->hand[i][k]);
          }	
          break;
        }		
      }	
    }
  }	
}
*/