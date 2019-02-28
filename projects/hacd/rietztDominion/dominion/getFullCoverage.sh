#!/bin/bash

function print2Ln(){
  echo; echo; echo "$1::$2 under test";
}

function print#Ln(){
  echo; echo "########################################################################################"; echo;
}

print2Ln ./unittest1 fullDeckCount > unittestresults.out
./unittest1 >> unittestresults.out
./getUnitCoverage.sh dominion.o fullDeckCount >> unittestresults.out

print2Ln ./unittest2 isGameOver >> unittestresults.out
./unittest2 >> unittestresults.out
./getUnitCoverage.sh dominion.o isGameOver >> unittestresults.out

print2Ln ./unittest3 handCard >> unittestresults.out
./unittest3 >> unittestresults.out
./getUnitCoverage.sh dominion.o handCard >> unittestresults.out

print2Ln ./unittest4 updateCoins >> unittestresults.out
./unittest4 >> unittestresults.out
./getUnitCoverage.sh dominion.o updateCoins >> unittestresults.out

print#Ln >> unittestresults.out
########################################################################################

print2Ln ./cardtest1 cardEffect >> unittestresults.out
./cardtest1 >> unittestresults.out
./getUnitCoverage.sh dominion.o cardEffect >> unittestresults.out

print2Ln ./cardtest1 smithyEffect >> unittestresults.out
./cardtest1 >> unittestresults.out
./getUnitCoverage.sh dominion.o smithyEffect >> unittestresults.out

print2Ln ./cardtest2 cardEffect >> unittestresults.out
./cardtest2 >> unittestresults.out
./getUnitCoverage.sh dominion.o cardEffect >> unittestresults.out

print2Ln ./cardtest2 adventurerEffect >> unittestresults.out
./cardtest2 >> unittestresults.out
./getUnitCoverage.sh dominion.o adventurerEffect >> unittestresults.out

print2Ln ./cardtest3 cardEffect >> unittestresults.out
./cardtest3 >> unittestresults.out
./getUnitCoverage.sh dominion.o cardEffect >> unittestresults.out

print2Ln ./cardtest3 cutPurseEffect >> unittestresults.out
./cardtest3 >> unittestresults.out
./getUnitCoverage.sh dominion.o cutPurseEffect >> unittestresults.out

print2Ln ./cardtest4 cardEffect >> unittestresults.out
./cardtest4 >> unittestresults.out
./getUnitCoverage.sh dominion.o cardEffect >> unittestresults.out

print2Ln ./cardtest4 villageEffect >> unittestresults.out
./cardtest4 >> unittestresults.out
./getUnitCoverage.sh dominion.o villageEffect >> unittestresults.out

print#Ln >> unittestresults.out
########################################################################################

gcov -b dominion.c >> unittestresults.out
print#Ln >> unittestresults.out
########################################################################################

gcov -f -b -c dominion.c >> unittestresults.out

echo "View unittestresults.out to see test and coverage results."

exit 0