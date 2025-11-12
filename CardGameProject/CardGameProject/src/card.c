/**
 * @file card.c
 * @brief Implementation of the Card helpers.
 */
#include "card.h"
#include <stdio.h>

static const char *SUIT_SYMBOLS[] = {"â£", "â ", "â¥", "â¦"}; /* ♣ ♠ ♥ ♦ */
static const char *RANK_STRINGS[] = {
    NULL, NULL, "2","3","4","5","6","7","8","9","10","J","Q","K","A"
};

void print_card(Card c)
{
    const char *rank = (c.rank >= 2 && c.rank <= 14) ? RANK_STRINGS[c.rank] : "?";
    const char *suit = (c.suit >= 0 && c.suit <= 3) ? SUIT_SYMBOLS[c.suit] : "?";
    printf("%s%s", rank, suit);
}

int compare_cards(Card a, Card b)
{
    if (a.rank != b.rank) return (int)a.rank - (int)b.rank;
    return (int)a.suit - (int)b.suit;
}
