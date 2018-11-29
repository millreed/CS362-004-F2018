/* -----------------------------------------------------------------------
* Unit tests for the buyCard function
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

int pass_fail(int cardBought, int expected) {
	if (cardBought == expected){
		return 1;
	}
	return 0;
}

int main() {
int i;
int failed = 0;
int seed = 1000;
int numPlayer = 4;
int p, r, cardBought;
int k[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map}; //Add all possible cards for testing purposes
struct gameState G;

printf("************* START OF TEST FOR buyCard *************\n\n");
memset(&G, 23, sizeof(struct gameState));   // clear the game state
r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
printf("Testing buyCard for %d players\n", numPlayer);
for (p = 0; p < numPlayer; p++)
{
	
	G.handCount[p] = 0;                 		// set the number of cards on hand to 0
	G.whoseTurn = p;							// set the game to the current player's turn
	
	for (i = 0; i<27; i++){
		G.numBuys = 0;							// set number of buys to 0 to test no buys
		cardBought = buyCard(k[i], &G);			// set cardBought to result of buyCard
#if (NOISY_TEST == 1)
		printf("Testing player %d numBuys = 0\n", p+1);
		if (!pass_fail(cardBought, -1)){
			failed++;
			printf("****FAILED*****");
		}
		else{
			printf("****PASSED****");
		};
		printf("Player %d\n cardBought = %d, expected = %d\n\n", p+1, cardBought,  -1);
#endif
		
		G.numBuys = 2;							// set number of buys to 2 to test actually buying cards
		G.supplyCount[k[i]] = 0;				// set supply of card to 0 to test no supply
		cardBought = buyCard(k[i], &G);			// set cardBought to result of buyCard
#if (NOISY_TEST == 1)
		printf("Testing player %d supplyCount = 0 \n", p+1);
		if (!pass_fail(cardBought, -1) || !pass_fail(G.numBuys, 2)){
			failed++;
			printf("****FAILED*****");
		}
		else{
			printf("****PASSED****");
		};
		printf("Player %d\n cardBought = %d, expected = %d\n numBuys = %d, expected = %d\n\n", p+1, cardBought,  -1, G.numBuys, 2);
#endif
		
		G.supplyCount[k[i]] = 2;				// set supply of card to 2 to test supply
		G.coins = getCost(k[i])-1;				// set # of coins = cost of card -1 to test if you can't afford the card
		cardBought = buyCard(k[i], &G);			// set cardBought to result of buyCard
#if (NOISY_TEST == 1)
		printf("Testing player %d for coins < cost\n", p+1);
		if (!pass_fail(cardBought, -1) || !pass_fail(G.numBuys, 2) || !pass_fail(G.supplyCount[k[i]], 2)){
			failed++;
			printf("****FAILED*****");
		}
		else{
			printf("****PASSED****");
		};
		printf("Player %d\n cardBought = %d, expected = %d\n numBuys = %d, expected = %d\n supplyCount = %d, expected = %d\n\n", p+1, cardBought,  -1, G.numBuys, 2, G.supplyCount[k[i]], 2);
#endif
		
		G.supplyCount[k[i]] = 2;				// set supply of card to 2 to test supply
		G.coins = 100;							// set # of coins = cost of card -1 to test if you can't afford the card
		cardBought = buyCard(k[i], &G);			// set cardBought to result of buyCard
		G.discardCount[p] = 0;					// set discardCount to 0 to see if it increases
#if (NOISY_TEST == 1)
		printf("Testing player %d for buying a Card\n", p+1);
		if (!pass_fail(cardBought, 0) || !pass_fail(G.numBuys, 1) || !pass_fail(G.supplyCount[k[i]], 1) || !pass_fail(G.coins, 100 - getCost(k[i])) || !pass_fail(G.phase, 1) || !pass_fail(G.discardCount[p], 1)){
			failed++;
			printf("****FAILED*****\n");
		}
		else{
			printf("****PASSED****\n");
		};
		printf("Player %d\n cardBought = %d, expected = %d\n numBuys = %d, expected = %d\n supplyCount = %d, expected = %d\n coins = %d, expected = %d\n phase = %d, expected = %d\n discardCount = %d, expected = %d \n\n", p+1, cardBought,  0, G.numBuys, 1, G.supplyCount[k[i]], 1, G.coins, 100 - getCost(k[i]), G.phase, 1, G.discardCount[p], 1);
#endif
		
		endTurn(&G);
	}
	
	
		
	
}

if (failed == 0){
	printf("All tests passed!\n\n");
}
else {
	printf("Failed %d Tests!\n\n", failed);
}

printf("************* END OF TEST FOR buyCard *************\n\n");

return 0;
}



