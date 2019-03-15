#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "asserttrue.h"
#include "rngs.h"





int main() {
	int testsFailed = 0;
	int numPlayer = 2;
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, great_hall, baron, village };
	int seed = 9000;
	struct gameState testGame;
	initializeGame(numPlayer, k, seed, &testGame);

	int handSize = numHandCards(&testGame);
	testsFailed += asserttrue(handSize == testGame.handCount[testGame.whoseTurn] );
	if (testsFailed > 0)
		printf("Tests failed\n");
	else
		printf("All tests passed\n");
	return 0;
}
