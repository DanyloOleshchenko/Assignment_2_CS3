/**
 * @file game.c
 * @brief Implementation of the two-player game logic.
 */
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

/* Helper to print a player's hand */
static void print_player(const char *label, const CardDeck *hand, void (*printer)(Card))
{
    printf("%s: ", label);
    for (size_t i = 0; i < hand->size; ++i) {
        printer(hand->cards[i]);
        if (i + 1 < hand->size) printf(" ");
    }
    printf("\n");
}

/* Check if card x matches top by suit or rank */
static int matches(Card x, Card top)
{
    return (x.suit == top.suit) || (x.rank == top.rank);
}

int game_play(size_t packs)
{
    CardDeck *hidden = deck_create(0);
    CardDeck *played = deck_create(0);
    CardDeck *p1 = deck_create(0);
    CardDeck *p2 = deck_create(0);
    if (!hidden || !played || !p1 || !p2) { fprintf(stderr, "Allocation failed.\n"); return 1; }

    /* Init and shuffle hidden deck */
    if (deck_init_standard_packs(hidden, packs) != 0) { fprintf(stderr, "Init failed.\n"); return 1; }
    if (deck_shuffle(hidden) != 0) { fprintf(stderr, "Shuffle failed.\n"); return 1; }

    /* Deal 8 cards alternately */
    for (int i = 0; i < 8; ++i) {
        Card c;
        deck_pop(hidden, &c); deck_push(p1, c);
        deck_pop(hidden, &c); deck_push(p2, c);
    }
    deck_sort(p1);
    deck_sort(p2);

    extern void print_card(Card); /* from card.c */
    print_player("Player 1", p1, print_card);
    print_player("Player 2", p2, print_card);

    /* Start played pile with top of hidden */
    Card top; deck_pop(hidden, &top); deck_push(played, top);
    printf("Start card: "); print_card(top); printf("\n");

    size_t turn = 0; /* 0: P1, 1: P2 */
    int winner = -1;
    int just_drew[2] = {0,0}; /* enforce 'cannot play drawn card until next turn' */

    while (winner < 0) {
        CardDeck *hand = (turn == 0) ? p1 : p2;
        const char *pname = (turn == 0) ? "Player 1" : "Player 2";

        /* find a playable card (first matching) if allowed */
        int played_this_turn = 0;
        if (!just_drew[turn]) {
            for (size_t i = 0; i < hand->size; ++i) {
                if (matches(hand->cards[i], played->cards[played->size-1])) {
                    Card played_card;
                    deck_remove_at(hand, i, &played_card);
                    deck_push(played, played_card);
                    printf("%s plays ", pname); print_card(played_card); printf("\n");
                    played_this_turn = 1;
                    break;
                }
            }
        }
        if (!played_this_turn) {
            /* draw one card */
            if (hidden->size == 0) {
                /* recycle played except top */
                if (played->size > 1) {
                    Card keep_top = played->cards[played->size-1];
                    CardDeck *tmp = deck_create(0);
                    /* move all but top into tmp */
                    for (size_t i = 0; i + 1 < played->size; ++i) deck_push(tmp, played->cards[i]);
                    deck_shuffle(tmp);
                    /* move tmp into hidden */
                    for (size_t i = 0; i < tmp->size; ++i) deck_push(hidden, tmp->cards[i]);
                    deck_free(tmp);
                    played->size = 1;
                    played->cards[0] = keep_top;
                    printf("Hidden deck empty — reshuffled played pile.\n");
                } else {
                    printf("No cards left to draw.\n");
                    break;
                }
            }
            Card drawn; deck_pop(hidden, &drawn);
            deck_push(hand, drawn);
            deck_sort(hand);
            just_drew[turn] = 1;
            printf("%s draws ", pname); print_card(drawn); printf("\n");
        } else {
            just_drew[turn] = 0;
        }

        print_player(pname, hand, print_card);
        if (hand->size == 0) { winner = (int)turn; break; }
        turn ^= 1;
    }

    if (winner >= 0) {
        printf("Game over — %s wins!\n", winner == 0 ? "Player 1" : "Player 2");
    }

    deck_free(hidden);
    deck_free(played);
    deck_free(p1);
    deck_free(p2);
    return 0;
}
