/* Christopher Beall
 * CS 362
 * Unit test for village
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "asserttrue.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

int main() {

	int fails;
	int r;
	int numPlayer = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, great_hall, baron, village};
	int seed = 9000;
	int bonus = 0;
	struct gameState game, copy;
	r = initializeGame(numPlayer, k, seed, &game);
	memcpy(&copy, &game, sizeof(struct gameState));	
	copy.hand[0][0] = village;	
	cardEffect(village, 0,0,0, &copy, 0, &bonus);	
	printf("%d\n", copy.discardCount[0]);
	printf("Test 1: villages effects worked\n");
	fails = 0;
	fails += asserttrue(copy.numActions == game.numActions + 2);		
	fails += asserttrue(copy.handCount[0] == game.handCount[0]);
	fails += asserttrue(copy.playedCards[copy.playedCardCount-1] == village);
	printf("%d\n", copy.discardCount[1]);
	if (fails)
		printf("Failed\n");
	else
		printf("Success\n");	

	printf("Test 2: Cards were drawn from players own deck\n");
	fails = 0;
	fails += asserttrue(copy.deckCount[0] == game.deckCount[0] - 1);	
	if (fails)
		printf("Failed\n");
	else
		printf("Success\n");	

	printf("Test 3: No state change for other player\n");
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


	printf("Test 4: Kingdom cards were not changed\n");
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
