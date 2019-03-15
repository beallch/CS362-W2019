/* Christopher Beall
 * CS 362
 * A unit test for the handCard function in dominion.c
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "asserttrue.h"
#include "rngs.h"

int main() {

	int fails = 0;
	int numPlayer = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, great_hall, baron, village };
	int seed = 9000;
	struct gameState game;
	initializeGame(numPlayer, k, seed, &game);

	printf("Test: The correct hand position is returned for the correct player.\n");
	game.hand[0][0] = adventurer;
	game.hand[0][1] = feast;
	game.hand[0][2] = gardens;
	game.handCount[0] = 3;
	game.hand[1][0] = mine;
	game.hand[1][1] = remodel;
	game.hand[1][2] = baron;
	game.whoseTurn = 0;
	int check = handCard(1, &game);
	
	fails += asserttrue(check == feast);
	if (fails)
		printf("Failed\n");
	else
		printf("Success\n");
}
