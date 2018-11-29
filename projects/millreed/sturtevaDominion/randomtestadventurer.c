/* -----------------------------------------------------------------------
* Random tests for the adventurer card
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
	int n, h, deck, dis, p, r, j;
	int tests = 2000;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};
	
	// Cards to fill deck, discard, and hand with
	int kt[17] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	
	int failures = 0;
	
	printf("************* START OF RANDOM TEST FOR adventurer card *************\n\n");
	
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
		if(floor(Random() * 3) <= 1.0){
			G.handCount[p] = floor(Random() * 10);
		}
		else {
			G.handCount[p] = floor(Random() * MAX_HAND); // set random hand size
		}
		
		// 1 in 3 chance to have smaller deck and discard piles
		if(floor(Random() * 3) <= 1.0){
			G.deckCount[p] = floor(Random() * 50);
			G.discardCount[p] = floor(Random() * 50);
		}
		else {
			G.deckCount[p] = floor(Random() * MAX_DECK); // set random deck size
			G.discardCount[p] = floor(Random() * (MAX_DECK - G.deckCount[p])); // set random discard count keeping the amount of cards less than MAX_DECK
		}

		int numTreasures = 0;
		int numHandTreasures = 0;
		
		// fill hand with random cards
		for (h = 0; h < G.handCount[p]; h++){
			j = floor(Random() * 16);
			G.hand[p][h] = kt[j];
			// check if card added to hand is a treasure card
			if (kt[j] == copper || kt[j] == silver || kt[j] == gold){
				numHandTreasures++;
			}
		}
		
		// fill deck with random cards
		for (deck = 0; deck < G.deckCount[p]; deck++){
			j = floor(Random() * 16);
			G.deck[p][deck] = kt[j];
			// check if card added to deck is a treasure card
			if (kt[j] == copper || kt[j] == silver || kt[j] == gold){
				numTreasures++;
			}
		}
		
		// fill discard pile with random cards
		for (dis = 0; dis < G.discardCount[p]; dis++){
			j = floor(Random() * 16);
			G.discard[p][dis] = kt[j];
			// check if at least two treasure cards are in deck + discard
			if (kt[j] == copper || kt[j] == silver || kt[j] == gold){
				numTreasures++;
			}
		}
		
		struct gameState GPrime;
		memcpy(&GPrime, &G, sizeof(struct gameState));
		
		// make sure there is at least 1 treasure card in the deck or discard pile
		if(numTreasures == 0){
			G.deck[p][0] = copper;
			numTreasures++;
		}
		
		//play card
		int adventurer = cardEffect(k[0], 0, 0, 0, &G, 0, 0);
		
		int numHandTreasuresPost = 0;
		
		// Count Treasures after playing card
		for (h = 0; h < G.handCount[p]; h++){
			if (G.hand[p][h] == copper || G.hand[p][h] == silver || G.hand[p][h] == gold){
				numHandTreasuresPost++;
			}
		}
		
		// check if function returns correctly
		if (adventurer != 0){
			printf("Test#%d: Failed, Adventurer function failed for input: handCount: %d, deckCount: %d, discardCount: %d, treasures: %d\n", n, GPrime.handCount[p], GPrime.deckCount[p], GPrime.discardCount[p], numHandTreasures);
			failures++;
		}
		
		
		else if(numTreasures < 2){
			// check the number of treasures in hand after playing the card
			if(numHandTreasures + 1 != numHandTreasuresPost){
				printf("Test#%d: Expected %d treasures, found %d treasures for input: handCount: %d, deckCount: %d, discardCount: %d, treasures: %d\n", n, numHandTreasures+1, numHandTreasuresPost, GPrime.handCount[p], GPrime.deckCount[p], GPrime.discardCount[p], numHandTreasures);
				failures++;
			}
			// check the handcount after playing the card
			else if (GPrime.handCount[p] + 1 != G.handCount[p]){
				printf("Test#%d: Expected %d handcount, found %d handcount for input: handCount: %d, deckCount: %d, discardCount: %d, treasures: %d\n", n, GPrime.handCount[p], G.handCount[p], GPrime.handCount[p], GPrime.deckCount[p], GPrime.discardCount[p], numHandTreasures);
				failures++;
			}
		}

		else {
			// check the number of treasures in hand after playing the card
			if(numHandTreasures + 2 != numHandTreasuresPost){
				printf("Test#%d Expected %d treasures, found %d treasures for input: handCount: %d, deckCount: %d, discardCount: %d, treasures: %d\n", n, numHandTreasures+1, numHandTreasuresPost, GPrime.handCount[p], GPrime.deckCount[p], GPrime.discardCount[p], numHandTreasures);
				failures++;
			}
			// check the handcount after playing the card
			else if (GPrime.handCount[p] + 2 != G.handCount[p]){
				printf("Test#%d: Expected %d handcount, found %d handcount for input: handCount: %d, deckCount: %d, discardCount: %d, treasures: %d\n", n, GPrime.handCount[p] + 1, G.handCount[p], GPrime.handCount[p], GPrime.deckCount[p], GPrime.discardCount[p], numHandTreasures);
				failures++;
			}
		}
		
	}
	
	if (failures > 0){
		printf("FAILED %d out of %d tests\n", failures, tests);
	}
	else{
		printf("PASSED all %d tests\n", tests);
	}
	printf("************* END OF RANDOM TEST FOR adventurer card *************\n\n");

	return 0;
}





