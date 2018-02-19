//This is for the random test of one of the cards: Using Council Room
#include "dominion.h"
#include <stdio.h>
#include "dominion_helpers.h"

#define NUMBER_OF_ITER 5
#define DEBUGIT 1
#define PLAYERS 6

void assert_Nums(int x, int y, int *number)

int main(){

        struct gameState G;

        int rand_number;
	int players_tot;

	players_tot = (rand() % 5) + 2;

	srand(time(0));
       
       
        int k[10] = {adventurer, gardens, embargo, village, minion, minie, cutpurse, sea_hag, tribute, smithy};
        initializeGame(players_tot, k, 1, &G);
        
        //int coin_one = -1;
        //int coin_two = -1;
        int card_one;
	int card_two;
	int card_three;
	int card_four;
	int draw_one;
        int draw_two;
	int draw_three;
	int draw_four;
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
	int initial_buy_in;
        int tempDeck[treasure_map];
	int hand_size_person[PLAYERS];
	int deck_size_person[PLAYERS];
	int discard_size_person[PLAYERS];
        
	printf("Coucil Room Card Testing\n");
        for(int i = 0; i < NUMBER_OF_ITER; i++){
        	printf("Iteration Number: %d\n", i + 1);
        
                //tempDeck[0] = -1;
                failed_test = 0;
                G.playedCount = 0;
                min_deck = 0;
                min_discard = 0;
                max_discard = rand() % MAX_HAND + 1;
                max_deck = MAX_HAND - max_discard;

                random_piles(&G, min_discard, max_discard, min_deck, max_deck);

                random_HandPos = rand() % G.handCount[G.whoseTurn];
                G.hand[G.whoseTurn][random_HandPos] = coucil_room;

                initial_count_card = G.handCount[G.whoseTurn] + G.discardCount[G.whoseTurn] + G.deckCount[G.whoseTurn];
                initial_score = scoreFor(state->whoseTurn, state);
                initial_count_deck = G.deckCount[G.whoseTurn];
                initial_count_discard = G.discardCount[G.whoseTurn];
                initial_count_hand = G.handCount[G.whoseTurn];
		initial_buy_in = G.numBuys;

                for(int i = 0; i < players_tot; i++){
			hand_size_person[i] = G.headCount[i];
			deck_size_person[i] = G.deckCount[i];
			discard_size_person[i] = G.discardCount[i];
		}

		draw_cards(card_one, card_two, card_three, card_four, &G);

		if(card_four == -1){
			dis_pile_count(tempDeck, treasure_map, &G);
			if(((card_one == -1) && (G.discardCount < 3)) || ((card_two == -1) && (G.discardCount < 2))||(G.discardCount < 1)){
				pringf("less then 4 cards to draw\n");
			}
		}

		council_room_play(&G, G.whoseTurn, random_HandPos);


                draw_one = G.hand[G.whoseTurn][G.handCount[G.whoseTurn] - 2];
                draw_two = G.hand[G.whoseTurn][G.handCount[G.whoseTurn] - 1];
		draw_three = G.hand[G.whoseTurn][random_HandPos];
		draw_four = G.handp[G.whoseTurn][random_HandPos];

		assertDrawCouncilRoom(card_one, card_two, card_three, card_four, draw_one, draw_two, draw_three, draw_four, tempDeck, failed_test);

                assertCC(initial_count_card, &G, failed_test);

                assertTotal(initial_score, &G, failed_test);

                if(card_four != -1){
                        assertDSize(initial_count_deck - 4, &G, failed_test);
			assertDisSize(initial_count_discard, &G, failed_test);
                }

                assertHandTot(initial_count_hand + 3, &G, failed_test)

		assertP2Draw(hand_size_person, deck_size_person, discard_size_person, &G, failed_test);

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

void draw_cards(int &card_one, int &card_two, int &card_three, int &card_four, struct gameState *state)
{
	int size_of_deck;
	card_one = -1;
	card_two = -1;
	card_three = -1;
	card_four = -1;

	size_of_deck = state->deckCount[state->whoseTurn];

	if(size_of_deck > 0){
		card_one = state->deckCount[state->whoseTurn][size_of_deck - 1];
	}
        if(size_of_deck > 1){
                card_two = state->deckCount[state->whoseTurn][size_of_deck - 2];
        }
        if(size_of_deck > 2){
                card_three = state->deckCount[state->whoseTurn][size_of_deck - 3];
        }
        if(size_of_deck > 3){
                card_four = state->deckCount[state->whoseTurn][size_of_deck - 4];
        }
}

void dis_pile_count(int *arr, int arrSize, struct gameState *state)
{
	int tempCard;
	for(int i = 0; i < arrSize; i++){
		arr[i] = 0;
	}

	for(int i = 0; i < state->discardCount[state->whoseTurn]; i++){
		tempCard = state->discard[state->whoseTurn][i];
		if((tempCard > treasure_map)||(tempCard < 0)){
			printf("Some issue\n");
		}else{
			arr[tempCard]++
		}
	}
}

void assertCRDraw(int card_one, int card_two, int card_three, int card_four, int draw_one, int draw_two, int draw_three, int draw_four, int *arr, int &failed_test)
{
	if(card_one == -1){
		arr[card_one]--;
	}else if(card_one){
		printf("Opps problem\n");
		failed_test = 1;
	}
        if(card_two == -1){
                arr[card_two]--;
        }else if(card_two){
                printf("Opps problem\n");
                failed_test = 1;
        }
        if(card_three == -1){
                arr[card_three]--;
        }else if(card_three){
                printf("Opps problem\n");
                failed_test = 1;
        }
        if(card_four == -1){
                arr[card_four]--;
        }else if(card_four){
                printf("Opps problem\n");
                failed_test = 1;
        }

	if(arr[draw_one] < 0){
		printf("Opps problem\n");
		failed_test = 1;
	}
        if(arr[draw_two] < 0){
                printf("Opps problem\n");
                failed_test = 1;
        }
        if(arr[draw_three] < 0){
                printf("Opps problem\n");
                failed_test = 1;
        }
        if(arr[draw_four] < 0){
                printf("Opps problem\n");
                failed_test = 1;
        }

	if(DEBUGIT && !failed_test)



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

void assertP2Draw(int *hand_size_person, int *deck_size_person, int *discard_size_person, struct gameState *state, int &failed_test)
{
	for(int i = 0; i < PLAYERS; i++){
		if(i != state->whoseTurn){
			if((hand_size_person[i] + 1) != state->handCount[i]){
				printf("Opps Problem\n");
				failed_test = 1;
			}
                        if((deck_size_person[i] + 1) != state->deckCount[i]){
                                printf("Opps Problem\n");
                                failed_test = 1;
                        }
                        if((discard_size_person[i] + 1) != state->discardCount[i]){
                                printf("Opps Problem\n");
                                failed_test = 1;
                        }
		}
	}
	if((DEBUGIT) && (!failed_test)){
		printf("good\n");
	}
}


void assertUsed(int count_used_want, struct gameState *state, int &failed_test)
{
        if(count_used_want != state->playedCount)||(state->played[state->playedCount - 1] != coucil_room){
                printf("Opps problem\n");
                failed_test = 1;
        }else if(DEBUGIT){
                printf("Good\n");
        }
}


//end

                                                                                                                                                                                                                  
