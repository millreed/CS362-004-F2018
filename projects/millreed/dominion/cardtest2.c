/* -----------------------------------------------------------------------
* Unit tests for the village card
* -----------------------------------------------------------------------
*/

#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "dominion_helpers.h"
#include <string.h>
#include <assert.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int pass_fail(int draw, int expected) {
	if (draw == expected){
		return 1;
	}
	return 0;
}

int main() {
int i;
int failed = 0;
int seed = 1000;
int numPlayer = 4;
int p, r;
int k[27] = {copper, silver, gold, curse, estate, duchy, province, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map}; //Add all possible cards for testing purposes
struct gameState G;

printf("************* START OF TEST FOR village card *************\n\n");
	
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

printf("Testing village for %d players\n", numPlayer);
for (p = 0; p < numPlayer; p++)
{
	G.whoseTurn = p;
	G.deckCount[p] = 0;                 		// set the number of cards on hand to 0

	// add one of each kingdom card to the player's deck with treasure cards first
	for (i = 0; i < 27; i++){
		G.deck[p][i] = k[i];
		G.deckCount[p]++;
	}
	int handCount = G.handCount[p]; //initialize handCount variable to current handCount
	int deckCount = G.deckCount[p]; //initialize deckCount variable to current deckCount
	int discardCount = G.discardCount[p]; //initialize discardCount variable to current discardCount
	int actions = G.numActions;			//initialize actions variable to the number of actions

	int village = cardEffect(k[14], 0, 0, 0, &G, 0, 0);  //Call village and set village variable to result

#if (NOISY_TEST == 1)
	// check if hand count is accurate
		printf("Testing player %d village card with 5 cards in hand and 1 action\n", p+1);
		if (!pass_fail(G.handCount[p], handCount) || !pass_fail(G.deckCount[p], deckCount-1) || !pass_fail(G.discardCount[p], discardCount) || !pass_fail(G.numActions, actions+1) || !pass_fail(village, 0)){
			failed++;
			printf("****FAILED*****\n");
		}
		else{
			printf("****PASSED****\n");
		};
		printf("Player %d\n handcount = %d, expected = %d\n deckCount = %d, expected = %d\n discardCount = %d, expected = %d\n actions = %d, expected = %d\n village return = %d, expected = %d\n\n", p+1, G.handCount[p], handCount, G.deckCount[p], deckCount-1, G.discardCount[p], discardCount, G.numActions, actions+1, village, 0);
#endif

	G.numActions = 3;
	G.handCount[p] = 5;
	G.discardCount[p] = 0;
	
	handCount = G.handCount[p]; //initialize handCount variable to current handCount
	deckCount = G.deckCount[p]; //initialize deckCount variable to current deckCount
	discardCount = G.discardCount[p]; //initialize discardCount variable to current discardCount
	actions = G.numActions;			//initialize actions variable to the number of actions
	
	village = cardEffect(k[14], 0, 0, 0, &G, 0, 0);  //Call village and set village variable to result
	
#if (NOISY_TEST == 1)
	// check if hand count is accurate
	printf("Testing player %d village card with 5 cards in hand and 3 actions\n", p+1);
	if (!pass_fail(G.handCount[p], handCount) || !pass_fail(G.deckCount[p], deckCount-1) || !pass_fail(G.discardCount[p], discardCount) || !pass_fail(G.numActions, actions+1) || !pass_fail(village, 0)){
		failed++;
		printf("****FAILED*****\n");
	}
	else{
		printf("****PASSED****\n");
	};
	printf("Player %d\n handcount = %d, expected = %d\n deckCount = %d, expected = %d\n discardCount = %d, expected = %d\n actions = %d, expected = %d\n village return = %d, expected = %d\n\n", p+1, G.handCount[p], handCount, G.deckCount[p], deckCount-1, G.discardCount[p], discardCount, G.numActions, actions+1, village, 0);
#endif
	
	endTurn(&G);
}
	
printf("************* END OF TEST FOR village card *************\n\n");
	
return 0;

}





