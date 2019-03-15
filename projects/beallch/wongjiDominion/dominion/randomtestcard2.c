#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "asserttrue.h"





int testMine(int p, struct gameState *change)
{
	int count = 0;
	struct gameState orig;
	change->hand[p][0] = 11; //set handPos 0 to the mine card to play it
	change->hand[p][1] = 4;
	change->hand[p][2] = 5;
	change->hand[p][3] = 6;
	change->hand[p][4] = 7;
	change->hand[p][5] = 3;
	memcpy(&orig, change, sizeof(struct gameState));
	// randomly choose a card from the players hand
	int choice1 = floor(Random() * 3 + 1);
	
	int choice2 = floor(Random() * 27 -1); //number between -1 and 25
	choice2 += floor(Random() * 3); // now makes the range -1 to 27, allows more testing
	
	
	int returnVal = cardMine(choice1, choice2, p, change, 0);

	count += asserttrue(returnVal == 0);
	//check for things that are changed by minion
	count += asserttrue(orig.hand[p][0] != change->hand[p][0]);

	//check that things that should not be changed are the same
	count += asserttrue(orig.numActions == change->numActions);
	count += asserttrue(orig.numBuys == change->numBuys);
	count += asserttrue(orig.deckCount[p] == change->deckCount[p]);
	count += asserttrue(orig.discardCount[p] + 2 == change->discardCount[p]);

}


int main() {
	int n;
	int p;
	struct gameState game;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		   sea_hag, tribute, smithy };
	int failCount = 0;
	int rand;
	for (n = 0; n < 200000; n++)
	{
		//initializeGame, then randomize things that mine can affect
		rand = Random() * 10000;
		initializeGame(2, k, rand, &game);
		p = floor(Random() * 2);
		game.deckCount[p] = floor(Random() * MAX_DECK);
		game.discardCount[p] = floor(Random() * MAX_DECK);
		game.handCount[p] = floor(Random() * MAX_HAND);
		
		failCount += testMine(p, &game);

	}
	printf("Failures: %d\n", failCount);
}
