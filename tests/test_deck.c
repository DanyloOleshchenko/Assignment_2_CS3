/**
 * @file test_deck.c
 * @brief Unit-style tests for deck operations.
 */
#include "common.h"
#include "../include/deck.h"
#include "../include/card.h"

static int is_sorted(const CardDeck *d)
{
    for (size_t i = 1; i < d->size; ++i) {
        Card a = d->cards[i-1];
        Card b = d->cards[i];
        if (a.rank > b.rank) return 0;
        if (a.rank == b.rank && a.suit > b.suit) return 0;
    }
    return 1;
}

int main(void)
{
    CardDeck *d = deck_create(0);
    ASSERT_TRUE(d != NULL);
    ASSERT_EQ_INT(0, deck_init_standard_packs(d, 1));
    ASSERT_EQ_INT(52, (int)d->size);

    /* Push/Pop */
    Card extra = {SUIT_SPADE, RANK_ACE};
    ASSERT_EQ_INT(0, deck_push(d, extra));
    ASSERT_EQ_INT(53, (int)d->size);
    Card popped;
    ASSERT_EQ_INT(0, deck_pop(d, &popped));
    ASSERT_EQ_INT(52, (int)d->size);

    /* Remove/Insert at */
    Card tmp;
    ASSERT_EQ_INT(0, deck_remove_at(d, 0, &tmp));
    ASSERT_EQ_INT(51, (int)d->size);
    ASSERT_EQ_INT(0, deck_insert_at(d, 0, tmp));
    ASSERT_EQ_INT(52, (int)d->size);

    /* Sort should produce non-decreasing order */
    deck_sort(d);
    ASSERT_TRUE(is_sorted(d));

    /* Shuffle should likely disturb order */
    ASSERT_EQ_INT(0, deck_shuffle(d));
    /* We can't guarantee different order, but for 52 cards it's extremely likely.
       We'll just check size preserved and not all equal to a sorted deck we create. */
    CardDeck *sorted = deck_create(0);
    deck_init_standard_packs(sorted, 1);
    deck_sort(sorted);
    int same = 1;
    for (size_t i = 0; i < d->size; ++i) {
        if (d->cards[i].rank != sorted->cards[i].rank || d->cards[i].suit != sorted->cards[i].suit) { same = 0; break; }
    }
    ASSERT_TRUE(!same);

    deck_free(sorted);
    deck_free(d);
    return 0;
}
