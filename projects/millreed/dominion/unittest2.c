/* -----------------------------------------------------------------------
* Unit tests for the handCard function
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

int pass_fail(int cardInHand, int handNum) {
	if (cardInHand == handNum){
		return 1;
	}
	return 0;
}

int main() {
int i;
int failed = 0;
int seed = 1000;
int numPlayer = 4;
int p, r, cardInHand;
int k[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map}; //Add all possible cards for testing purposes
struct gameState G;

printf("************* START OF TEST FOR handCard *************\n\n");
memset(&G, 23, sizeof(struct gameState));   // clear the game state
r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

printf("Testing handCard for %d players\n", numPlayer);
for (p = 0; p < numPlayer; p++)
	{
		#if (NOISY_TEST == 1)
		printf("Testing player %d\n", p+1);
		#endif
		
		G.handCount[p] = 0;                 // set the number of cards on hand
		G.whoseTurn = p;							// set whoseTurn to current player to test
		for (i = 0; i < 27; i++){				//fill player's hand with all kingdom cards
			G.hand[p][i] = k[i];
			cardInHand = handCard(i, &G);
		#if (NOISY_TEST == 1)
			if (!pass_fail(cardInHand, k[i])){
				failed++;
				printf(" ****FAILED*****");
			}
			else{
				printf(" ****PASSED****");
			};
			printf("Player %d's %d card in hand = %d, expected = %d\n\n", p+1, i, cardInHand, k[i]);
		#endif
		}
		endTurn(&G);
	}
	
	if (failed == 0){
	printf("All tests passed!\n\n");
	}
	else {
	printf("Failed %d Tests!\n\n", failed);
	}
	printf("************* END OF TEST FOR handCard *************\n\n");

return 0;
}


