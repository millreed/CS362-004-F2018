/* -----------------------------------------------------------------------
* Unit tests for the smithy card
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
int k[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map}; //Add all possible cards for testing purposes
struct gameState G;

printf("************* START OF TEST FOR smithy Card *************\n\n");

	
	
r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

	for (i = 0; i < sizeof(struct gameState); i++) {
		printf("%d\n", ((char*)&G)[i]);
	}
	
printf("Testing smithy for %d players\n", numPlayer);
for (p = 0; p < numPlayer; p++)
{
    G.deckCount[p] = 0; 	// set the number of cards on hand to 0
	G.whoseTurn = p;
	
	// add one of each kingdom card to the player's deck for testing purposes
	for (i = 0; i < 27; i++){
		G.deck[p][i] = k[i];
		G.deckCount[p]++;
	}
	int handCount = G.handCount[p]; //initialize handcount variable to current handCount
	
	int smithy = cardEffect(k[13], 0, 0, 0, &G, 0, 0);  //call smithy_card
	
#if (NOISY_TEST == 1)
	// check if hand count is accurate
		printf("Testing player %d Smithy Card with 5 card in hand\n", p+1);
		if (!pass_fail(G.handCount[p], handCount+2) || !pass_fail(smithy, 0)){
			failed++;
			printf("****FAILED*****\n");
		}
		else{
			printf("****PASSED****\n");
		};
		printf("Player %d\n handcount = %d, expected = %d\n smithy return = %d, expected = %d\n\n", p+1, G.handCount[p], handCount+2, smithy, 0);
#endif
	
	G.handCount[p] = 100;
	handCount = G.handCount[p]; //initialize handcount variable to current handCount
	
	smithy = cardEffect(k[13], 0, 0, 0, &G, 0, 0);  //call smithy_card
	
#if (NOISY_TEST == 1)
	// check if hand count is accurate
	printf("Testing player %d Smithy Card with 100 cards in hand\n", p+1);
	if (!pass_fail(G.handCount[p], handCount+2) || !pass_fail(smithy, 0)){
		failed++;
		printf("****FAILED*****\n");
	}
	else{
		printf("****PASSED****\n");
	};
	printf("Player %d\n handcount = %d, expected = %d\n smithy return = %d, expected = %d\n\n", p+1, G.handCount[p], handCount+2, smithy, 0);
#endif
	
	G.handCount[p] = 0;
	handCount = G.handCount[p]; //initialize handcount variable to current handCount
	
	smithy = cardEffect(k[13], 0, 0, 0, &G, 0, 0);  //call smithy_card
	
#if (NOISY_TEST == 1)
	// check if hand count is accurate
	printf("Testing player %d Smithy Card with 0 cards in hand\n", p+1);
	if (!pass_fail(G.handCount[p], handCount+2) || !pass_fail(smithy, 0)){
		failed++;
		printf("****FAILED*****\n");
	}
	else{
		printf("****PASSED****\n");
	};
	printf("Player %d\n handcount = %d, expected = %d\n smithy return = %d, expected = %d\n\n", p+1, G.handCount[p], handCount+2, smithy, 0);
#endif
	endTurn(&G);
	}

if (failed == 0){
	printf("All tests passed!\n\n");
}
else {
	printf("Failed %d Tests!\n\n", failed);
}

printf("************* END OF TEST FOR smithy Card *************\n\n");

return 0;
}




