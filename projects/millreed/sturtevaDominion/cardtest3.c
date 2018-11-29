/* -----------------------------------------------------------------------
* Unit tests for the cutpurse card
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
int i, j, numCoppers;
int failed = 0;
int seed = 1000;
int numPlayer = 4;
int p, r;
int k[27] = {copper, silver, gold, curse, estate, duchy, province, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map}; //Add all possible cards for testing purposes
struct gameState G;

printf("************* START OF TEST FOR cutpurse card *************\n\n");

	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
printf("Testing cutpurse for %d players\n", numPlayer);
for (p = 0; p < numPlayer; p++)
{
	G.whoseTurn = p;
	
	printf("It is Player %d's turn\n", G.whoseTurn+1);
	
	//initialize the coins variable to hold the initial amount of coins
	int coins = G.coins;
	
	//initialize all players hands to non-copper cards
	for (i = 0; i < numPlayer; i++){
		G.handCount[i] = 5;
		for (j=0; j< 5; j++){
			G.hand[i][j] = k[1];
		}
	}
	
	//add different amounts of copper cards to each player's hand
	for (j = 0; j < 3; j++){
		G.hand[p][j] = k[0];
	}
	
	for (j = 0; j < 2; j++){
		G.hand[(p+1)%4][j] = k[0];
	}
	
	G.hand[(p+2)%4][j] = k[0];
	
	printf("Copper amounts for each player pre cutpurse call:\n");
	for (i = 0; i < numPlayer; i++){
		numCoppers = 0;
		for (j=0; j< 5; j++){
			if (G.hand[i][j] == copper){
				numCoppers += 1;
			}
		}
		printf("Player %d Coppers: %d\n", i+1, numCoppers);
	}
	
	//set variables for the handCount for each player
	int handCount = G.handCount[p];
	int handCount1 = G.handCount[(p+1)%4];
	int handCount2 = G.handCount[(p+2)%4];
	int handCount3 = G.handCount[(p+3)%4];
	
	G.hand[p][4] = cutpurse;
	
	//call the card function
	
	
	int cutpurse = playCard(4, -1, -1, -1, &G);  //Call cutpurse and set village variable to result
	
#if (NOISY_TEST == 1)
	// check if hand count is accurate
	printf("Testing player %d cutpurse card play\n", p+1);
	printf("Copper amounts for each player post cutpurse call:\n");
		for (i = 0; i < numPlayer; i++){
			numCoppers = 0;
			for (j=0; j< 5; j++){
				if (G.hand[i][j] == copper){
					numCoppers += 1;
				}
			}
			printf("Player %d Coppers: %d\n", i+1, numCoppers);
		}
		if (!pass_fail(G.handCount[p], handCount-1) || !pass_fail(G.handCount[(p+1)%4], handCount1-1) || !pass_fail(G.handCount[(p+2)%4], handCount2-1) || !pass_fail(G.handCount[(p+3)%4], handCount3) || !pass_fail(G.coins, coins+2) || !pass_fail(cutpurse, 0)){
			failed++;
			printf("****FAILED*****\n");
		}
		else{
			printf("****PASSED****\n");
		};
	printf("Player %d's handcount = %d, expected = %d\n Player %d's handCount = %d, expected = %d\n Player %d's handCount = %d, expected = %d\n Player %d's handCount = %d, expected = %d\n coins = %d, expected = %d\n cutpurse return = %d, expected = %d\n\n", p%4+1, G.handCount[p], handCount-1, (p+1)%4+1, G.handCount[(p+1)%4], handCount1-1, (p+2)%4+1, G.handCount[(p+2)%4], handCount2-1, (p+3)%4+1, G.handCount[(p+3)%4], handCount3, G.coins, coins+2, cutpurse, 0);
#endif
	endTurn(&G);
}

printf("************* END OF TEST FOR cutpurse card *************\n\n");

return 0;

}






