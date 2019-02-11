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
	struct gameState copy;
	initializeGame(numPlayer, k, seed, &game);
	
	
	memcpy(&copy, &game, sizeof(struct gameState));
 	//test 1
	printf("Test 1: gain card to discard\n");
	gainCard(adventurer, &copy, 0, 0);
	fails += asserttrue(game.discardCount[0] + 1 == copy.discardCount[0]);
	if (fails)
		printf("Failure\n");
	else
		printf("Success\n");

	//test 2
	printf("Test 2: gain card to deck\n");
	fails = 0;
	gainCard(adventurer, &copy, 1, 0);
	fails += asserttrue(game.deckCount[0] + 1 == copy.deckCount[0]);
	if (fails)
		printf("Failure\n");
	else
		printf("Success\n");

	//test 3
	printf("Test 3: Gain card to hand\n");
	fails = 0;
	gainCard(adventurer, &copy, 2, 0);
	fails += asserttrue(game.handCount[0] + 1 == copy.handCount[0]);
	if (fails)
		printf("Failure\n");
	else
		printf("Success\n");
	//test 4: to make sure other player was not affected
	fails = 0;
	printf("Test 4: Other players state unaffected\n");
	int i;
	for (i = 0; i < game.handCount[1]; i++)
		fails += asserttrue(game.hand[1][i] == copy.hand[1][i]);

	for (i = 0; i < game.deckCount[1]; i++)
		fails += asserttrue(game.deck[1][i] == copy.deck[1][i]);
	
	for (i = 0; i < game.discardCount[1]; i++)
		fails += asserttrue(game.discard[1][i] == copy.discard[1][i]);
	if (fails)
		printf("Failure\n");
	else
		printf("Success\n");

	//Test 5	
	printf("Test 5: Drawn card is decreased\n");
	fails = 0;
	fails += asserttrue(copy.supplyCount[adventurer] == game.supplyCount[adventurer] - 3);
	if (fails)
		printf("Failure\n");
	else
		printf("Success\n");
	
	return 0;
}
