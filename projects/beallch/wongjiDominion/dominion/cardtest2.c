/* Christopher Beall
 * CS 362
 * unit test for the smithy card */

#include "dominion.h"
#include "dominion_helpers.h"
#include "asserttrue.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>
int main() {

	int fails = 0;
	int r;
	int numPlayer = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, great_hall, baron, village};
	int seed = 9000;
	int bonus = 0;
	struct gameState game, copy;
	r = initializeGame(numPlayer, k, seed, &game);
	memcpy(&copy, &game, sizeof(struct gameState));
	copy.whoseTurn = 0;
	cardEffect(smithy, 0,0,0, &copy, 0, &bonus);
	
	printf("Test 1: The player recieves 3 cards\n");
	fails = 0;
	int playedSize = copy.playedCardCount -1;
	fails += asserttrue(copy.handCount[0] -2 == game.handCount[0]);


	if (fails)
		printf("Failed\n");
	else
		printf("Success\n");


	printf("Test 2: The cards came from their own deck\n");
	fails = 0;
	fails += asserttrue(copy.deckCount[0] < game.deckCount[0]);
	fails += asserttrue(copy.deckCount[1] == game.deckCount[1]);
	
	if (fails)
		printf("Failed\n");
	else
		printf("Success\n");	
		
	printf("Test 3: No state change for other players\n");
	fails = 0;
	int i;
	fails += asserttrue(copy.handCount[1] == game.handCount[1]);
	if (!fails)
	{
	for (i = 0; i< game.handCount[1]; i++)
		fails += asserttrue(copy.hand[1][i] == game.hand[1][i]);
	}
	fails += asserttrue(copy.deckCount[1] == game.deckCount[1]);
	if (!fails)
	{
	for (i = 0; i < game.deckCount[1]; i++)
		fails += asserttrue(copy.deck[1][i] == game.deck[1][i]);
	}
	fails += asserttrue(copy.discardCount[1] == game.discardCount[1]);
	if (!fails)
	{
	for (i = 0; i < game.discardCount[1]; i++)
		fails += asserttrue(copy.discard[1][i] == game.discard[1][i]);
	}
	if (fails)
		printf("Failed\n");
	else
		printf("Success\n");
	
	printf("Test 4: No state changes for kingdom card piles\n");
	fails = 0;
	fails += asserttrue(copy.supplyCount[adventurer] == game.supplyCount[adventurer]);
	fails += asserttrue(copy.supplyCount[council_room] == game.supplyCount[council_room]);
	fails += asserttrue(copy.supplyCount[feast] == game.supplyCount[feast]);
	fails += asserttrue(copy.supplyCount[gardens] == game.supplyCount[gardens]);
	fails += asserttrue(copy.supplyCount[mine] == game.supplyCount[mine]);
	fails += asserttrue(copy.supplyCount[remodel] == game.supplyCount[remodel]);
	fails += asserttrue(copy.supplyCount[smithy] == game.supplyCount[smithy]);
	fails += asserttrue(copy.supplyCount[great_hall] == game.supplyCount[great_hall]);
	fails += asserttrue(copy.supplyCount[baron] == game.supplyCount[baron]);
	fails += asserttrue(copy.supplyCount[village] == game.supplyCount[village]);
	if (fails)
		printf("Failed\n");
	else
		printf("Success\n");

	return 0;

}
