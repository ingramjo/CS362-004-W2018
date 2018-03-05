//unit test for ending a turn


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set CARD_TEST to 0 to remove printfs from output

#define CARD_TEST 1

int main() {
	int testsPassed = 0;
	int testsFailed = 0;
	int i;
	int seed = 1000;
	int numPlayer = 3;
	int maxBonus = 10;
	int p, r, handCount, toState;
	int bonus;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	struct gameState G;
	int maxHandCount = 5;

    // arrays of all coppers, silvers, and golds
	int coppers[MAX_HAND];
	int silvers[MAX_HAND];
	int golds[MAX_HAND];
	for (i = 0; i < MAX_HAND; i++)
	{
		coppers[i] = copper;
		silvers[i] = silver;
		golds[i] = gold;
	}

	printf ("TESTING endTurn():\n");

#if (CARD_TEST == 1)

	printf("Testing Ending a Turn.\n", p);

#endif

	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	G.whoseTurn = 0;
	G.numActions = 0;
	G.numBuys = 0;
	endTurn(&G);
	int numCoins = updateCoins(G.whoseTurn, &G , 0);

#if (CARD_TEST == 1)

	printf("Turn ended, it is now the turn of %d, expected %d\n", G.whoseTurn, 1);
	printf("G.numActions are %d, expected %d\n", G.numActions, 1);
	printf("G.numBuys are %d, expected %d\n", G.numBuys, 1);
	printf("Number of cards in next player's hand %d, expected %d\n", G.handCount[G.whoseTurn], 5);

#endif

	if(G.whoseTurn == 1){
		testsPassed++;
	}else {
		testsFailed++;
	}

	if(G.numActions == 1){
		testsPassed++;
	}else {
		testsFailed++;
	}

        if(G.numBuys == 1){
		testsPassed++;
	}else {
		testsFailed++;
	}

        if(G.handCount[G.whoseTurn] == 5){
		testsPassed++;
	}else {
		testsFailed++;
	}

	printf("Tests passed: %d\n",testsPassed);
	printf("Tests failed: %d\n",testsFailed);

	return 0;

}
