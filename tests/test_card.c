/**
 * @file test_card.c
 * @brief Unit-style tests for card helpers.
 */
#include "common.h"
#include "../include/card.h"

int main(void)
{
    Card a = {SUIT_SPADE, RANK_FIVE};
    Card b = {SUIT_HEART, RANK_FIVE};
    Card c = {SUIT_HEART, RANK_SIX};

    /* Same rank, different suit */
    ASSERT_TRUE(compare_cards(a, b) != 0);

    /* Rank order */
    ASSERT_TRUE(compare_cards(c, b) > 0); /* six > five */

    /* Enum sanity */
    ASSERT_EQ_INT(0, SUIT_CLUB);
    ASSERT_EQ_INT(3, SUIT_DIAMOND);
    ASSERT_EQ_INT(2, RANK_TWO); /* in this design, TWO has value 2 */
    ASSERT_EQ_INT(14, RANK_ACE);

    return 0;
}
