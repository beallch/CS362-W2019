#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "asserttrue.h"





int testAdventurer(int p, struct gameState *change)
{
	int count = 0;
	struct gameState orig;
	memcpy(&orig, change, sizeof(struct gameState));
	int temphand[MAX_HAND];
	int returnVal = adventurerFunc(0, p, change, temphand, 0);

	count += asserttrue(returnVal == 0);
	//check for things that are changed by adventurer
	count += asserttrue(orig.handCount[p] + 2 == change->handCount[p]);
	
	//check that things that should not be changed are the same
	count += asserttrue(orig.numActions == change->numActions);
	count += asserttrue(orig.numBuys == change->numBuys);
	return count;
}


int main() {
	int n;
	int p;
	struct gameState game;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		   sea_hag, tribute, smithy };
	int failCount = 0;
	int rand;
	for (n = 0; n < 2000; n++) 
	{
		rand = Random() * 10000;
		//initializeGame, then randomize things that adventurer can affect
		initializeGame(2, k, rand, &game);
		p = floor(Random() * 2);
		game.deckCount[p] = floor(Random() * MAX_DECK);
		game.discardCount[p] = floor(Random() * MAX_DECK);
		game.handCount[p] = floor(Random() * MAX_HAND);
		failCount += testAdventurer(p, &game);

	}
	printf("Failures: %d\n", failCount);
}