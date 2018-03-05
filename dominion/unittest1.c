#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


// set CARD_TEST to 0 to remove printfs from output

 #define CARD_TEST 1

int main(){
	int testsPassed = 0;
	int testsFailed = 0;
	int i;
 	int seed = 1000;
	int numPlayer = 2;
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

	printf ("TESTING gainCards():\n");

	for (p = 0; p < numPlayer; p++)
	{

#if (CARD_TEST == 1)

		printf("Test player %d.\n", p);

#endif

		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
		G.handCount[p] = 5;                 // set the number of cards on hand
		memcpy(G.hand[p], coppers, sizeof(int) * 5); // set all the cards to copper
		gainCard(k[0], &G, 1, p); //test adding card to players deck

#if (CARD_TEST == 1)

		printf("Card added to deck= %d, expected = %d\n", G.deck[p][G.deckCount[p]-1], k[0]);
		printf("G.deckCount = %d, expected = %d\n", G.deckCount[p], 6);          

#endif

		if(G.deck[p][G.deckCount[p]-1] == k[0]){
			testsPassed++;
		}else {
			testsFailed++;
                }

		if(G.deckCount[p] == 6){
			testsPassed++;
		}else{
			testsFailed++;
		}

		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
 		G.handCount[p] = 5;                 // set the number of cards on hand
		memcpy(G.hand[p], coppers, sizeof(int) * 5); // set all the cards to copper
		gainCard(k[0], &G, 0, p);//test adding card to player's discard pile

#if (CARD_TEST == 1)

		printf("Card added to discard= %d, expected = %d\n", G.discard[p][ G.discardCount[p]-1], k[0]);
		printf("G.discardCount = %d, expected = %d\n", G.discardCount[p], 1);

#endif

	}
	
	printf("Tests passed: %d\n",testsPassed);
	printf("Tests failed: %d\n",testsFailed);

	return 0;

}















