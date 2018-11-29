/* -----------------------------------------------------------------------
 * Unit tests for the numHandCards function
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

int pass_fail(int cardsInHand, int handCount) {
	if (cardsInHand == handCount){
		return 1;
	}
	return 0;
}

int main() {
	int failed = 0;
	int seed = 1000;
	int numPlayer = 4;
	int p, r, handCount;
	int cardsInHand;
	int k[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int maxHandCount = 20;
	
	printf("************* START OF TEST FOR numHandCards *************\n\n");
	printf("Testing numHandCards for %d players with hands up to %d cards\n", numPlayer, MAX_HAND);
	for (p = 0; p < numPlayer; p++)
	{
		for (handCount = 0; handCount <= maxHandCount; handCount++)
		{
			#if (NOISY_TEST == 1)
							printf("Testing player %d with %d cards in hand.\n", p+1, handCount);
			#endif
							memset(&G, 23, sizeof(struct gameState));   // clear the game state
							r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
							G.handCount[p] = handCount;                 // set the number of cards on hand
							G.whoseTurn = p;							// set whoseTurn to current player to test
							cardsInHand = numHandCards(&G);				// call numHandCards for current gameState
			#if (NOISY_TEST == 1)
						if (!pass_fail(cardsInHand, handCount)){		// check if the number of cards in hand is correct
							failed++;									// if test fails, increment the failed counter
							printf("****FAILED***** ");
						}
						else{
							printf("****PASSED**** ");
						};
						printf("Player %d cards in hand = %d, expected = %d\n\n", p+1, cardsInHand, handCount);
			#endif
					}
	}
	
	if (failed == 0){
		printf("All tests passed!\n");
	}
	else {
		printf("Failed %d Tests!\n", failed);
	}
	
	printf("************* END OF TEST FOR numHandCards *************\n\n");
	
	return 0;
}

