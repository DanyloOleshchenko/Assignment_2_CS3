/**
 * @file test_main.c
 * @brief Minimal placeholder for unit-style checks (optional).
 */
#include "card.h"
#include "deck.h"
#include <stdio.h>

int main(void)
{
    Card a = {SUIT_SPADE, RANK_FIVE};
    Card b = {SUIT_HEART, RANK_FIVE};
    printf("compare_cards(a,b) = %d\n", compare_cards(a, b));
    CardDeck *d = deck_create(0);
    deck_init_standard_packs(d, 1);
    deck_shuffle(d);
    deck_sort(d);
    printf("Deck has %zu cards after sort.\n", d->size);
    deck_free(d);
    return 0;
}
