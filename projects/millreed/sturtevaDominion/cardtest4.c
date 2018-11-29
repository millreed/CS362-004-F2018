/* -----------------------------------------------------------------------
* Unit tests for the adventurer card
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

printf("************* START OF TEST FOR adventurer card *************\n\n");
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
printf("Testing adventurer for %d players\n", numPlayer);
for (p = 0; p < numPlayer; p++)
{
	G.deckCount[p] = 0;                 		// set the number of cards on hand to 0
	
	// add one of each kingdom card to the player's deck with treasure cards first
	for (i = 0; i < 27; i++){
		G.deck[p][i] = k[i];
		G.deckCount[p]++;
	}
	int handCount = G.handCount[p]; //initialize handCount variable to current handCount
	int deckCount = G.deckCount[p]; //initialize deckCount variable to current deckCount
	int discardCount = G.discardCount[p]; //initialize discardCount variable to current discardCount
	
	int adventurer = cardEffect(k[7], 0, 0, 0, &G, 0, 0);  //Call adventurer and set adventurer variable to result
	

	
#if (NOISY_TEST == 1)
	// check if hand count is accurate
		printf("Testing player %d adventurer card with treasure cards in front of deck\n", p+1);
		if (!pass_fail(G.handCount[p], handCount+2) || !pass_fail(G.deckCount[p], deckCount-2) || !pass_fail(G.discardCount[p], discardCount) || !pass_fail(adventurer, 0)){
			failed++;
			printf("****FAILED*****\n");
		}
		else{
			printf("****PASSED****\n");
		};
		printf("Player %d's handcount = %d, expected = %d\n deckCount = %d, expected = %d\n discardCount = %d, expected = %d\n adventurer return = %d, expected = %d\n\n", p, G.handCount[p], handCount+2, G.deckCount[p], deckCount-2, G.discardCount[p], discardCount, adventurer, 0);
#endif
	
	G.deckCount[p] = 0;                 		// set the number of cards on hand to 0
	
	// add one of each kingdom card to the player's deck with treasure cards last
	for (i = 26; i >=0; i--){
		G.deck[p][i] = k[i];
		G.deckCount[p]++;
	}
	handCount = G.handCount[p]; //initialize handCount variable to current handCount
	deckCount = G.deckCount[p]; //initialize deckCount variable to current deckCount
	discardCount = G.discardCount[p]; //initialize discardCount variable to current discardCount
	
	adventurer = cardEffect(k[7], 0, 0, 0, &G, 0, 0);  //Call adventurer and set adventurer variable to result
	
	
#if (NOISY_TEST == 1)
	// check if hand count is accurate
	printf("Testing player %d adventurer card with treasure cards in back of deck\n", p+1);
	if (!pass_fail(G.handCount[p], handCount+2) || !pass_fail(G.deckCount[p], deckCount-26) || !pass_fail(G.discardCount[p], discardCount+24) || !pass_fail(adventurer, 0)){
		failed++;
		printf("****FAILED*****\n");
	}
	else{
		printf("****PASSED****\n");
	};
	printf("Player %d's handcount = %d, expected = %d\n deckCount = %d, expected = %d\n discardCount = %d, expected = %d\n adventurer return = %d, expected = %d\n\n", p, G.handCount[p], handCount+2, G.deckCount[p], deckCount-26, G.discardCount[p], discardCount+24, adventurer, 0);
#endif
	
	endTurn(&G);
	}

if (failed == 0){
	printf("All tests passed!\n\n");
}
else {
	printf("Failed %d Tests!\n\n", failed);
}

printf("************* END OF TEST FOR adventurer card *************\n\n");

return 0;
}





