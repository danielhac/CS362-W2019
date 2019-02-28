/*****************************************************************************************************************************
* adventurer
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
  int initialTreasure = 0;
  int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
  
  struct gameState* state = newGame();
  newTestInstance(players, kingdomCards, seed, state);
  int player = whoseTurn(state);

  state->hand[player][handPos] = adventurer;

/*
* adventurer::adds2Treasure
*/
  char* testName = "adventurer::adds2Treasure";
  initialTreasure = getTreasure(player, state);
  cardEffect(adventurer, 0, 0, 0, state, handPos, 0);
  if(getTreasure(player, state) != initialTreasure + 2){
    result = 0;
  }
  assertTrue(result, &overallResult, testName, 0);

/*
* adventurer::handCount+=1
*/
  testName = "adventurer::handCount+=1";
  resetResult(&result);
  int initialHandCount = state->handCount[player];
  cardEffect(adventurer, 0, 0, 0, state, handPos, 0);
  if(state->handCount[player] != initialHandCount + 1){
    result = 0;
  }
  assertTrue(result, &overallResult, testName, 0);

/*
* adventurer::doesShuffle
*/
  testName = "adventurer::doesShuffle";
  resetResult(&result);
  state->deckCount[player] = 0;
  cardEffect(adventurer, 0, 0, 0, state, handPos, 0);
  if(state->deckCount[player] <= 0){
    result = 0;
  }
  assertTrue(result, &overallResult, testName, 0);

/*
* adventurer::discardGrows
*/
  testName = "adventurer::discardGrows";
  resetResult(&result);
  int lastCard = state->deck[player][state->deckCount[player]-1];
  int almostLastCard = state->deck[player][state->deckCount[player]-2];
  int initialDiscardCount = state->discardCount[player];
  while(isTreasure(lastCard) || isTreasure(almostLastCard)){
    shuffle(player, state);
  }
  cardEffect(adventurer, 0, 0, 0, state, handPos, 0);
  if(state->discardCount[player] <= initialDiscardCount || state->discardCount[player] < 2){
    result = 0;
  }
  assertTrue(result, &overallResult, testName, 0);

  testName = "adventurer::OVERALL";
  assertTrue(result, &overallResult, testName, 1);

  return 0;
}


/*
void adventurerEffect(int drawntreasure, int currentPlayer, int nextPlayer, struct gameState *state, int* temphand){
  int z=0, cardDrawn;
  while(drawntreasure<2){
    if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
      shuffle(currentPlayer, state);
    }
    drawCard(currentPlayer, state);
    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
      drawntreasure++;
    else{
      temphand[z]=cardDrawn;
      state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
      z++;
    }
  }
  while(z-1==0){     //BUG: should be 'z-1>=0'
    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }
}
*/