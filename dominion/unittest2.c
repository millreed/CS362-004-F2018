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
#define NOISY_TEST 0

int pass_fail(int cardsInHand, int handCount) {
if (cardsInHand == handCount){
return 1;
}
return 0;
}

int main() {
int i;
int failed = 0;
int seed = 1000;
int numPlayer = 4;
int maxBonus = 10;
int p, r, handCount;
int cardsInHand;
int k[10] = {adventurer, council_room, feast, gardens, mine
, remodel, smithy, village, baron, great_hall};
struct gameState G;
int maxHandCount = MAX_HAND;

printf("Testing numHandCards for %d players with hands up to %d cards\n", numPlayer, MAX_HAND);
for (p = 0; p < numPlayer; p++)
{
for (handCount = 0; handCount <= maxHandCount; handCount++)
{
#if (NOISY_TEST == 1)
printf("Test player %d with %d cards in hand.\n", p+1, handCount);
#endif
memset(&G, 23, sizeof(struct gameState));   // clear the game state
r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
G.handCount[p] = handCount;                 // set the number of cards on hand
G.whoseTurn = p;							// set whoseTurn to current player to test
cardsInHand = numHandCards(&G);				// call numHandCards for current gameState
#if (NOISY_TEST == 1)
printf("Player %d cards in hand = %d, expected = %d\n", p+1, cardsInHand, handCount);
#endif
if (!pass_fail(cardsInHand, handCount)){
failed++;
printf("FAILED\n");
}; 			// check if the number of cards in hand is correct
}
}
if (failed == 0){
printf("All tests passed!\n");
}
else {
printf("Failed %d Tests!\n", failed);
}

return 0;
}


