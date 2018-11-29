/* -----------------------------------------------------------------------
 * Random tests for the council room card
 * -----------------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <math.h>


int main() {
	int i, n, h, deck, dis, p, r, j;
	int tests = 2000;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};
	
	// Cards to fill deck, discard, and hand with
	int kt[17] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	struct gameState G;
	
	int failures = 0;
	
	printf("************* START OF RANDOM TEST FOR council room card *************\n\n");
	
	for (n = 0; n < tests; n++) {
		int numPlayer = 2 + floor(Random() * 2); // random number of players between 2 and 4
		int seed = floor(Random() * 10000); // random seed
		int stream =  floor(Random() * 256); // random stream generator
		SelectStream(stream);
		
		// random gamestate
		r = initializeGame(numPlayer, k, seed, &G);
		
		p = 2 + floor(Random() * (numPlayer - 2)); // choose random player between 2 and numPlayer
		
		G.whoseTurn = p;
		
		// 1 in 3 chance to have smaller hand size
		for (i = 0; i < numPlayer; i++){
			if(floor(Random() * 3) <= 1.0){
				G.handCount[i] = 1 + floor(Random() * 10);
			}
			else {
				G.handCount[i] = 1 + floor(Random() * (MAX_HAND -1)); // set random hand size
			}
		}
		
		// 1 in 3 chance to have smaller deck and discard piles
		if(floor(Random() * 3) <= 1.0){
			G.deckCount[p] = floor(Random() * 50);
			G.discardCount[p] = floor(Random() * 50);
		}
		else {
			G.deckCount[p] = 3 + floor(Random() * (MAX_DECK - 3)); // set random deck size
			G.discardCount[p] = floor(Random() * ((MAX_DECK - 3) - G.deckCount[p])); // set random discard count keeping the amount of cards less than MAX_DECK
		}
		
		// fill each player's hand with random cards
		for (i = 0; i < numPlayer; i++){
			for (h = 0; h < G.handCount[i]; h++){
				j = floor(Random() * 16);
				G.hand[i][h] = kt[j];
			}
		}
		
		
		// fill deck with random cards
		for (deck = 0; deck < G.deckCount[p]; deck++){
			j = floor(Random() * 16);
			G.deck[p][deck] = kt[j];
		}
		
		// fill discard pile with random cards
		for (dis = 0; dis < G.discardCount[p]; dis++){
			j = floor(Random() * 16);
			G.discard[p][dis] = kt[j];
		}
		
		struct gameState GPrime;
		memcpy(&GPrime, &G, sizeof(struct gameState));
		
		//play card
		int council_room = cardEffect(k[1], 0, 0, 0, &G, 0, 0);
		
		// check if function returns correctly
		if (council_room != 0){
			printf("Test#%d: Failed, Council Room function failed for input: handCount: %d, deckCount: %d, discardCount: %d, buys: %d\n", n, GPrime.handCount[p], GPrime.deckCount[p], GPrime.discardCount[p], GPrime.numBuys);
			failures++;
		}
	
		else {
			int pass = 1;
			// check the number of treasures in hand after playing the card
			if(GPrime.handCount[p] + 3 != G.handCount[p]){
				printf("Test#%d Expected %d handcount, found %d handcount for input: handCount: %d, deckCount: %d, discardCount: %d, buys: %d\n", n, GPrime.handCount[p] + 3, G.handCount[p], GPrime.handCount[p], GPrime.deckCount[p], GPrime.discardCount[p], GPrime.numBuys);
				pass &= 0;
			}
			// check the deck count after playing the card
			if(GPrime.deckCount[p] < 4){
				if (GPrime.deckCount[p] + GPrime.discardCount[p] - 3 != G.deckCount[p]){
					printf("Test#%d: Expected %d deckCount, found %d deckCount for input: handCount: %d, deckCount: %d, discardCount: %d, buys: %d\n", n, GPrime.deckCount[p] + GPrime.discardCount[p] - 3, G.deckCount[p], GPrime.handCount[p], GPrime.deckCount[p], GPrime.discardCount[p], GPrime.numBuys);
					pass &= 0;
				}
			}
			else{
				if (GPrime.deckCount[p] - 3 != G.deckCount[p]){
					printf("Test#%d: Expected %d deckCount, found %d deckCount for input: handCount: %d, deckCount: %d, discardCount: %d, buys: %d\n", n, GPrime.deckCount[p] - 3, G.deckCount[p], GPrime.handCount[p], GPrime.deckCount[p], GPrime.discardCount[p], GPrime.numBuys);
					pass &= 0;
				}
			}
			
			// check the buys after playing the card
			if (GPrime.numBuys+1 != G.numBuys){
				printf("Test#%d: Expected %d buys, found %d buys for input: handCount: %d, deckCount: %d, discardCount: %d, buys: %d\n", n, GPrime.numBuys+1 , G.numBuys, GPrime.handCount[p], GPrime.deckCount[p], GPrime.discardCount[p], GPrime.numBuys);
				pass &= 0;
			}
			
			// check other players hand counts
			for (i = 0; i < numPlayer; i++){
				if (i != p){
					if (GPrime.handCount[i] + 1 != G.handCount[i]){
						printf("Test#%d: Expected %d handcount for Player %d, found %d handcount for input: handCount: %d, deckCount: %d, discardCount: %d, buys: %d\n", n, GPrime.handCount[i]+1, i, G.handCount[i], GPrime.handCount[p], GPrime.deckCount[p], GPrime.discardCount[p], GPrime.numBuys);
						pass &= 0;
					}
				}
			}
			
			
			if (!pass){
				failures++;
			}
			
			// check the opponent's hand counts after playing the card
		}
		
	}
	
	if (failures > 0){
		printf("FAILED %d out of %d tests\n", failures, tests);
	}
	else{
		printf("PASSED all %d tests\n", tests);
	}
	printf("************* END OF RANDOM TEST FOR smithy card *************\n\n");
	
	return 0;
}





