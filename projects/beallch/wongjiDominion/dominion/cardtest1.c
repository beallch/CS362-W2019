/* Christopher Beall
 * CS 362
 * Unit test for adventurer card
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "asserttrue.h"
#include "rngs.h"
#include <string.h>
int main() {

	int fails = 0;
	struct gameState game, copy;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, great_hall, baron, village };
	int seed = 9000;
	initializeGame(2, k, seed, &game);
	memcpy(&copy, &game, sizeof(struct gameState));
	int bonus;


	printf("Test 1: Normal play of card\n");
	cardEffect(adventurer, 0, 0, 0, &copy, 0, &bonus);//This useage of the card will be tested with
	fails += asserttrue(copy.handCount[0] + 1 == game.handCount[0]);
	if (fails)
		printf("Failure\n");
	else
		printf("Success\n");

	fails = 0;
	printf("Test 2: Drawn cards were treasure\n");
	fails += asserttrue(copy.hand[0][copy.handCount[0]-2] == copper || copy.hand[0][copy.handCount[0]-2] == silver || copy.hand[0][copy.handCount[0]-2] == gold);
	fails += asserttrue(copy.hand[0][copy.handCount[0]-1] == copper || copy.hand[0][copy.handCount[0]-1] == silver || copy.hand[0][copy.handCount[0]-1] == gold);

	if (fails)
		printf("Failure\n");
	else
		printf("Success\n");

	fails = 0;
	printf("Test 3: other player maintained state\n");
	int i;
	fails += asserttrue(copy.handCount[1] == game.handCount[1]);
	for  (i = 0; i < game.handCount[1]; i++)
		fails += asserttrue(copy.hand[1][i] == game.hand[1][i]);
	fails += asserttrue(copy.deckCount[1] == game.deckCount[1]);
	for (i = 0; i< game.deckCount[1]; i++)
		fails += asserttrue(copy.deck[1][i] == game.deck[1][i]);
	fails += asserttrue(copy.discardCount[1] == game.discardCount[1]);

	for (i = 0; i < game.discardCount[1]; i++)
		fails += asserttrue(copy.discard[1][i] == game.discard[1][i]);

	if (fails)
		printf("Failed\n");
	else
		printf("Success\n");
			

	return 0;
}
