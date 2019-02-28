#include "dominion.h"
#include "dominion_helpers.h"
#include "testHelpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void newTestInstance(int players, int kingdomCards[10], int seed, struct gameState* state){
  initializeGame(players, kingdomCards, seed, state);
}

void assertTrue(int testResult, int* overallResult, char* testName, int isOverall){
  if(isOverall){
    if(*overallResult == 1){
      printf("----------------------------------------------------%s\n\tPASSED\n\n", testName);
    } else {
      printf("----------------------------------------------------%s\n\tFAILED\n\n", testName);
    }
    return;
  }
  
  if(testResult == 1){
    printf("----------------------------------------------------%s\n\tPASSED\n\n", testName);
  } else {
    printf("----------------------------------------------------%s\n\tFAILED\n\n", testName);
    *overallResult = 0;
  }
}

void resetResult(int* result){
  *result = 1;
}

int isTreasure(int card){
  if(card == gold || card == silver || card == copper){
    return 1;
  }
  return 0;
}

int getTreasure(int player, struct gameState* state){
  int treasure, i;
  treasure = i = 0;
  while(i < state->handCount[player]){
    if( isTreasure(state->hand[player][i]) ){
      treasure++;
    }
    i++;
  }
  return treasure;
}

int getTreasureVal(int player, struct gameState* state){
  int treasure, i, card;
  treasure = i = 0;
  while(i < state->handCount[player]){
    card = state->hand[player][i];
    if( card == gold ){
      treasure += 3;
    } else if(card == silver){
      treasure += 2;
    } else if(card == copper){
      treasure += 0;
    }
    i++;
  }
  return treasure;
}

