//This file is for the adventurer card for assignment 4
//


#include "dominion.h"
#include <stdio.h>
#include "dominion_helpers.h"

#define NUMBER_OF_ITER 5 
#define DEBUGIT 1

void assert_Nums(int x, int y, int *number)

int main(){

	struct gameState G;

	//create random number
	int rand_number;
	srand(time(0));

	//copying over from playdom.c
	int k[10] = {adventurer, gardens, embargo, village, minion, minie, cutpurse, sea_hag, tribute, smithy};

	initializeGame(2, k, 1, &G);

	//initialize of variables
	int coin_one = -1;
	int coin_two = -1;
	int draw_one;
	int draw_two;
	int random_HandPos;
	int test_count_fail = 0;
	int test_count_pass = 0;
	int failed_test = 0;
	int initial_count_card;
	int initial_score;
	int initial_count_deck;
	int initial_count_discard;
	int initial_count_hand;
	int initial_count_play;
	int tempDeck[MAX_HAND];

	printf("Adventurer Card Testing\n");

	for(int i = 0; i < NUMBER_OF_ITER; i++){
		printf("Iteration Number: %d\n", i + 1);

		//next sequence is to reset for the iteration
		tempDeck[0] = -1;
		failed_test = 0;
		G.playedCount = 0;
		min_deck = 0;
		min_discard = 0;
		max_discard = rand() % MAX_HAND + 1;
		max_deck = MAX_HAND - max_discard;

		random_piles(&G, min_discard, max_discard, min_deck, max_deck);
		
		random_HandPos = rand() % G.handCount[G.whoseTurn];
		G.hand[G.whoseTurn][random_HandPos] = adventurer;

		initial_count_card = G.handCount[G.whoseTurn] + G.discardCount[G.whoseTurn] + G.deckCount[G.whoseTurn];
		initial_score = scoreFor(state->whoseTurn, state);
		initial_count_deck = G.deckCount[G.whoseTurn];
		initial_count_discard = G.discardCount[G.whoseTurn];
		initial_count_hand = G.handCount[G.whoseTurn];
		
		coin_count(tempDeck, MAX_HAND - 1, coin_one, coin_two, &G);

		if(coin_two == -1){
			coin_used(copperCount, silverCount, goldCount, &G);
			if((copperCount + silverCount + goldCount) == 1){
				if(coin_one == -1){
					printf("1 coin is left\n");
				}
			}else if((copperCount + silverCount + goldCount) == 0){
				printf("No coin left\n");
			}
		} 
	
		adventurer_play(&G, G.whoseTurn);

		draw_one = G.hand[G.whoseTurn][G.handCount[G.whoseTurn] - 1];
		draw_two = G.hand[G.whoseTurn][random_HandPos];

		
		assertCD(draw_one, draw_two, coin_one, coin_two, copperCount, silverCount, goldCount, failed_test);


		assertCC(initial_count_card, &G, failed_test);

		assertTotal(initial_score, &G, failed_test);

		if(coin_two != -1){
			i = 0;
			while(tempDeck[i] != -1){
				i++;
			}
			assertDSize(initial_count_deck - (2 + i), &G, failed_test);
		}

		if(coin_two != -1){
			assertDisSize(initial_count_discard + i, &G, failed_test)
		}

		assertHandTot(initial_count_hand + 2, &G, failed_test)

		assertUsed(1, &G, failed_test);

		test_count_fail += failed_test;

	}

	return 0;
}

void random_piles(struct gameState *state, int discard_min, int discard_max, int deck_min, int deck_max)
{
	int card_amount;
	int add_card;
	

	card_amount = (rand()%(discard_max + 1)) + discard_min;
	state->discardCount[state->whoseTurn] = card_amount;

	for(int i = 0; i < card_amount; i++){
		add_card = rand()%(treasure_map + 1);
		state->discard[state->whoseTurn][i] = add_card;
	}

	card_amount = (rand()%(deck_max + 1)) + deck_min;
	state->deckCount[state->whoseTurn] = card_amount;

	for(int i = 0; i < card_amount; i++){
		card_amount = rand()%(treasure_map + 1);
		state->deck[state->whoseTurn][i] = add_card;
	}
}

void coin_count(int *no_coin, int coin_max_no, int &coin_1, int &coin_2, struct gameState *state)
{
	int no_coin_idx = 0;
	coin_1 = -1;
	coin_2 = -1;
	int next_card;

	for(int i = 0; ((i < coin_max_no) && (coin_2 == -1)); i++){
		next_card = state->deck[state->whoseTurn][i];
		if((next_card == copper) || (next_card == silver) || (next_card == gold)){
			if (coin_1 == -1){
				coin_1 = next_card;
			} else {
				coin_2 = next_card;
			}
		}else{
			no_coin[no_coin_idx] = next_card;
			no_coin_idx++;
		}
	}
	no_coin[no_coin_idx] = -1;
}

void coin_used(int &coperCount, int &silverCount, int & goldCount, struct gameState *state)
{
	int tempCard;
	copperCount = 0;
	silverCount = 0;
	goldCount = 0:

	for(int i = 0; i < state->discardCount[state->whoseTurn]; i++){
		tempCard = state->discard[state->whoseTurn][i];
		if(temCard == copper){
			copperCount++;
		}else if(tempCard == silver){
			silverCount++;
		}else if(tempCard == gold){
			goldCount++;
		}
	}
} 

void assertCD(int draw_one, int draw_two, int coin_one, int coin_two, int copperCount, int silverCount, int goldCount, int &failed_test)
{
	if(coin_two == -1){
		if(coin_one == -1){
			if(draw_one == copper){
				copperCount--;
			}else if(draw_one == silver){
				silverCount--;
			}else if(draw_one == golf){
				goldCount--;
			}else{
				printf("Card drawn after Adventure card not a coin\n");
				failed_test = 1;
			}
		}else{
			if(draw_two == copper){
				copperCount--;
			}else if(draw_two == silver){
				silverCount--;
			}else if(draw_two == gold){
				goldCount--;
			}else{
				printf("Card drawn after Adventur card not a coin\n");
				failed_test = 1;
			}
		}

		if(copperCount < 0){
			printf("Copper added to no existing hand\n");
			failed_test = 1;
		}
                if(silverCount < 0){
                        printf("Silver added to no existing hand\n");
                        failed_test = 1;
                }
                if(goldCount < 0){
                        printf("Gold added to no existing hand\n");
                        failed_test = 1;
                }
	}else{
		if(draw_one != coin_one){
                        printf("Card added to hand that did not exist\n");
                        failed_test = 1;
                }
                if(draw_two != coin_two){
                        printf("Card added to hand that did not exist\n");
                        failed_test = 1;
                }
	}

	if(DEBUGIT && !failed_test){
		printf("Test Pass\n");
	}
}

void assertCC(int count_deck_p, struct gameState *state, int &failed_test)
{
	int count_start;
	count_start = state->handCount[state->whoseTurn] + state->discardCount[state->whoseTurn] + state->deckCount[state->whoseTurn];

	if(count_deck_p != new_deck){
		printf("Opps problem\n");
		failed_test = 1;
	}else if(DEBUGIT){
		printf("Good\n");
	}
}

void assertTotal(int prev_total, struct gameState *state, int &failed_test)
{
	int new_total;
	new_total = scoreFor(state->whoseTurn, state);

	if(prev_total != new_total){
		printf("Opps problem\n");
		failed_test = 1;
	}else if(DEBUGIT){
		printf("Good\n");
	}
}

void assertDSize(int deck_size_want, struct gameState *state, int &failed_test)
{
	if(deck_size_want != state->deckCount[state->whoseTurn]){
		printf("Opps problem\n");
		failed_test = 1;
	}else if(DEBUGIT){
		printf("Good\n");
	}
}

void assertDisSize(int discard_size_want, struct gameState *state, int &failed_test)
{
        if(discard_size_want != state->discardCount[state->whoseTurn]){
        	printf("Opps problem\n");
		faile_test = 1;
        }else if(DEBUGIT){
                printf("Good\n");
        }
}

void assertHandTot(int hand_size_want, struct gameState *state, int &failed_test)
{
	if(hand_size_want != state->handCount[state->whoseTurn]){
		printf("Opps problem\n");
		failed_test = 1;
	}else if(DEBUGIT){
		printf("Good\n");
	}
}

void assertUsed(int count_used_want, struct gameState *state, int &failed_test)
{
        if(count_used_want != state->playedCount)||(state->played[state->playedCount - 1] != adventurer){
        	printf("Opps problem\n");
		failed_test = 1;
        }else if(DEBUGIT){
                printf("Good\n");
        }
}


//end 
