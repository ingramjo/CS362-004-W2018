//Unit test for testing a game is over

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

    // arrays of all coppers, silvers, and gold
	int coppers[MAX_HAND];
	int silvers[MAX_HAND];
	int golds[MAX_HAND];

	for (i = 0; i < MAX_HAND; i++)
	{
		coppers[i] = copper;
		silvers[i] = silver;
		golds[i] = gold;
	}

	printf ("TESTING isGameOver():\n");

#if (CARD_TEST == 1)

	printf("Testing with new game.\n", p);

#endif

	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	int rValue = isGameOver(&G);

#if (CARD_TEST == 1)

	printf("New game is not over and return value is %d, expected %d\n",rValue, 0);

#endif

	if(rValue == 0){
		testsPassed++;
	} else {
		testsFailed++;
	}

#if (CARD_TEST == 1)

	printf("Testing with empty province .\n", p);

#endif

	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	G.supplyCount[province] = 0;
	rValue = isGameOver(&G);

#if (CARD_TEST == 1)

	printf("Game is over and return value is %d, expected %d\n",rValue, 1);

#endif

	if(rValue == 1){
		testsPassed++;
	} else {
		testsFailed++;
	}

#if (CARD_TEST == 1)

	printf("Testing 3 empty supply piles .\n", p);

#endif

	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	G.supplyCount[copper] = 0;
	G.supplyCount[estate] = 0;
	G.supplyCount[adventurer] = 0;
	rValue = isGameOver(&G);

#if (CARD_TEST == 1)

	printf("Game is over and return value is %d, expected %d\n",rValue, 1);

#endif

	if(rValue == 1){
		testsPassed++;
	} else {
		testsFailed++;
	}

	printf("Tests passed: %d\n",testsPassed);
	printf("Tests failed: %d\n",testsFailed);

	return 0;

}
