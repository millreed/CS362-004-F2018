/* -----------------------------------------------------------------------
* Unit tests for the fullDeckCount function
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

int pass_fail(int count, int expected) {
	if (count == expected){
		return 1;
		
	}
	return 0;
}

int main() {
int failed = 0;
int seed = 1000;
int numPlayer = 4;
int p, r;
int k[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room};
struct gameState G;

printf("************* START OF TEST FOR fullDeckCount *************\n\n");
printf("Testing fullDeckCount for %d players\n", numPlayer);
memset(&G, 23, sizeof(struct gameState));   // clear the game state
r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
for (p = 0; p < numPlayer; p++)
{
	// set deck, hand, and discard counts to 6 to hold all test cards
	G.deckCount[p] = 6;
	G.handCount[p] = 6;
	G.discardCount[p] = 6;
	
	//Add card 0 to all piles, card 1 to deck and discard, card 2 to deck and hand, card 3 to hand and discard, card 4 to deck, card 5 to hand, card 6 to discard, and card 8 to all piles twice
	
	G.deck[p][0] = k[0];
	G.deck[p][1] = k[1];
	G.deck[p][2] = k[2];
	G.deck[p][3] = k[4];
	G.deck[p][4] = k[8];
	G.deck[p][5] = k[8];
	G.hand[p][0] = k[0];
	G.hand[p][1] = k[2];
	G.hand[p][2] = k[3];
	G.hand[p][3] = k[5];
	G.hand[p][4] = k[8];
	G.hand[p][5] = k[8];
	G.discard[p][0] = k[0];
	G.discard[p][1] = k[1];
	G.discard[p][2] = k[3];
	G.discard[p][3] = k[6];
	G.discard[p][4] = k[8];
	G.discard[p][5] = k[8];

	// set count variables equal to the result of fullDeckCount for each card
	
	int count1 = fullDeckCount(p, k[0], &G);
	int count2 = fullDeckCount(p, k[1], &G);
	int count3 = fullDeckCount(p, k[2], &G);
	int count4 = fullDeckCount(p, k[3], &G);
	int count5 = fullDeckCount(p, k[4], &G);
	int count6 = fullDeckCount(p, k[5], &G);
	int count7 = fullDeckCount(p, k[6], &G);
	int count8 = fullDeckCount(p, k[7], &G);
	int count9 = fullDeckCount(p, k[8], &G);
	
	
#if (NOISY_TEST == 1)
		//check if the counts are correct
		printf("Testing player %d for card counts\n", p+1);
		if (!pass_fail(count1, 3) || !pass_fail(count2, 2) || !pass_fail(count3, 2) || !pass_fail(count4, 2) || !pass_fail(count5, 1) || !pass_fail(count6, 1) || !pass_fail(count7, 1) || !pass_fail(count8, 0) || !pass_fail(count9, 6)){
			failed++;
			printf("****FAILED*****\n");
		}
		else{
			printf("****PASSED****\n");
		};
	printf("Player %d's deck counts are:\n curse = %d, expected = %d\n estate = %d, expected = %d\n duchy = %d, expected = %d\n province = %d, expected = %d\n copper = %d, expected = %d\n silver = %d, expected = %d\n gold = %d, expected = %d\n adventurer = %d, expected = %d\n council_room = %d, expected = %d\n \n\n", p+1, count1, 3, count2, 2, count3, 2, count4, 2, count5, 1, count6, 1, count7, 1, count8, 0, count9, 6);
#endif

}

if (failed == 0){
	printf("All tests passed!\n\n");
}
else {
	printf("Failed %d Tests!\n\n", failed);
}

printf("************* END OF TEST FOR fullDeckCount *************\n\n");

return 0;
}




