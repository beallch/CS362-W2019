/* Christopher Beall
 * CS 362
 * A unit test for the discardCard Function 
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
	struct gameState game, copy;
	initializeGame(numPlayer, k, seed, &game);
	memcpy(&copy, &game, sizeof(struct gameState));

	
	printf("Test 1: Last card is removed from hand\n");
	//add a card to the playedCard list to test for
	copy.playedCards[copy.playedCardCount] = feast;
	copy.playedCardCount++;
	int lastCard = copy.handCount[0] - 1;
	copy.hand[0][lastCard] = adventurer;	

	discardCard(4, 0, &copy, 0);
	fails += asserttrue(copy.hand[0][4] == -1);
	fails += asserttrue(copy.playedCards[copy.playedCardCount - 1] == adventurer);
	fails += asserttrue(copy.handCount[0] == game.handCount[0] - 1);
	if (fails)
		printf("Failed\n");
	else
		printf("Success\n");

	printf("Test 2: last card is removed and trashed\n");
	memcpy(&copy, &game, sizeof(struct gameState));
	fails = 0;
	lastCard = copy.handCount[0] - 1;
	copy.playedCards[copy.playedCardCount] = feast;
	copy.playedCardCount++;
	copy.hand[0][lastCard] = adventurer;
	
	discardCard(lastCard , 0 , &copy, 1);
	fails += asserttrue(copy.hand[0][4] == -1);
	fails += asserttrue(copy.playedCards[copy.playedCardCount -1] == feast);
	fails += asserttrue(copy.handCount[0] == game.handCount[0] -1);
	if (fails)
		printf("Failed\n");
	else
		printf("Success\n");

	printf("Test 3: Only one card in hand\n");
	fails = 0;
	memcpy(&copy, &game, sizeof(struct gameState));
	
	copy.playedCards[copy.playedCardCount] = feast;
	copy.playedCardCount++; 
	copy.handCount[0] = 1;
	copy.hand[0][0] = adventurer;
	
	discardCard(0, 0, &copy, 0);
	
	fails += asserttrue(copy.handCount[0] == 0);
	fails += asserttrue(copy.playedCards[copy.playedCardCount - 1] == adventurer);
	
	if (fails)
		printf("Failed\n");
	else
		printf("Success\n");
	
	
	printf("Test 4: Middle card in hand\n");
	fails = 0;
	memcpy(&copy, &game, sizeof(struct gameState));
	copy.hand[0][0] = adventurer;
	copy.hand[0][1] = smithy;
	copy.hand[0][2] = baron;
	copy.handCount[0] = 3;

	discardCard(1, 0, &copy, 0);

	fails += asserttrue(copy.handCount[0] == 2);
	fails += asserttrue(copy.playedCards[copy.playedCardCount - 1] == smithy);
	fails += asserttrue(copy.hand[0][1] == baron);

	if (fails)
		printf("Failed\n");
	else
		printf("Success\n");
	
	printf("Test 5: Other player is not affected\n");
	fails = 0;
	memcpy(&copy, &game, sizeof(struct gameState));
	discardCard(4,0, &copy, 0);
	discardCard(0, 0, &copy, 0);
	discardCard(1, 0, &copy, 0);

	int i;
	for (i = 0; i < copy.handCount[1]; i++)
		fails += asserttrue(copy.hand[1][i] == game.hand[1][i]);
	fails += asserttrue(copy.handCount[1] == game.handCount[1]);
	if (fails)
		printf("Failed\n");
	else
		printf("Success\n");
	return 0;	
}
