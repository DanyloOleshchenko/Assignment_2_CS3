/**
 * @file deck.c
 * @brief Implementation of the CardDeck operations with dynamic memory.
 */
#include "deck.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int deck_grow(CardDeck *deck, size_t min_capacity)
{
    size_t newcap = deck->capacity ? deck->capacity : 16;
    while (newcap < min_capacity) newcap *= 2;
    Card *p = (Card*)realloc(deck->cards, newcap * sizeof(Card));
    if (!p) return -1;
    deck->cards = p;
    deck->capacity = newcap;
    return 0;
}

CardDeck* deck_create(size_t initial_capacity)
{
    CardDeck *d = (CardDeck*)calloc(1, sizeof(CardDeck));
    if (!d) return NULL;
    if (initial_capacity) {
        d->cards = (Card*)malloc(initial_capacity * sizeof(Card));
        if (!d->cards) { free(d); return NULL; }
        d->capacity = initial_capacity;
    }
    d->size = 0;
    return d;
}

void deck_free(CardDeck *deck)
{
    if (!deck) return;
    free(deck->cards);
    free(deck);
}

int deck_reserve(CardDeck *deck, size_t needed)
{
    if (deck->capacity >= needed) return 0;
    return deck_grow(deck, needed);
}

int deck_push(CardDeck *deck, Card c)
{
    if (deck->size == deck->capacity) {
        if (deck_grow(deck, deck->size + 1) != 0) return -1;
    }
    deck->cards[deck->size++] = c;
    return 0;
}

int deck_pop(CardDeck *deck, Card *out)
{
    if (deck->size == 0) return -1;
    if (out) *out = deck->cards[deck->size - 1];
    deck->size--;
    return 0;
}

int deck_remove_at(CardDeck *deck, size_t index, Card *out)
{
    if (index >= deck->size) return -1;
    if (out) *out = deck->cards[index];
    memmove(&deck->cards[index], &deck->cards[index + 1], (deck->size - index - 1) * sizeof(Card));
    deck->size--;
    return 0;
}

int deck_insert_at(CardDeck *deck, size_t index, Card c)
{
    if (index > deck->size) return -1;
    if (deck->size == deck->capacity) {
        if (deck_grow(deck, deck->size + 1) != 0) return -1;
    }
    memmove(&deck->cards[index + 1], &deck->cards[index], (deck->size - index) * sizeof(Card));
    deck->cards[index] = c;
    deck->size++;
    return 0;
}

int deck_init_standard_packs(CardDeck *deck, size_t packs)
{
    if (!deck || packs < 1) return -1;
    deck->size = 0;
    if (deck_reserve(deck, packs * 52) != 0) return -1;
    for (size_t p = 0; p < packs; ++p) {
        for (int s = SUIT_CLUB; s <= SUIT_DIAMOND; ++s) {
            for (int r = RANK_TWO; r <= RANK_ACE; ++r) {
                Card c; c.suit = (Suit)s; c.rank = (Rank)r;
                if (deck_push(deck, c) != 0) return -1;
            }
        }
    }
    return 0;
}

int deck_shuffle_to(const CardDeck *source, CardDeck *dest)
{
    if (!source || !dest) return -1;
    /* Copy source to a temporary mutable array */
    Card *tmp = (Card*)malloc(source->size * sizeof(Card));
    if (!tmp) return -1;
    memcpy(tmp, source->cards, source->size * sizeof(Card));
    size_t N = source->size;
    dest->size = 0;
    if (deck_reserve(dest, N) != 0) { free(tmp); return -1; }
    /* Seed RNG once per process */
    static int seeded = 0;
    if (!seeded) { srand((unsigned)time(NULL)); seeded = 1; }
    while (N > 0) {
        size_t r = (size_t)(rand() % N);  /* 0..N-1 */
        Card picked = tmp[r];
        /* Move picked to start of dest (index 0 is "top") by inserting at 0 */
        deck_insert_at(dest, 0, picked);
        /* Remove r-th from tmp by shifting */
        memmove(&tmp[r], &tmp[r+1], (N - r - 1) * sizeof(Card));
        --N;
    }
    free(tmp);
    return 0;
}

int deck_shuffle(CardDeck *deck)
{
    if (!deck) return -1;
    CardDeck *tmp = deck_create(deck->size);
    if (!tmp) return -1;
    int rc = deck_shuffle_to(deck, tmp);
    if (rc == 0) {
        /* swap buffers */
        free(deck->cards);
        deck->cards = tmp->cards;
        deck->size = tmp->size;
        deck->capacity = tmp->capacity;
        /* prevent double-free */
        tmp->cards = NULL;
    }
    deck_free(tmp);
    return rc;
}

/* Simple insertion sort by compare_cards (rank then suit) */
void deck_sort(CardDeck *deck)
{
    if (!deck) return;
    for (size_t i = 1; i < deck->size; ++i) {
        Card key = deck->cards[i];
        size_t j = i;
        while (j > 0) {
            int cmp = 0;
            /* inline compare to avoid dependency on card.c here */
            if (deck->cards[j-1].rank != key.rank) {
                cmp = (int)deck->cards[j-1].rank - (int)key.rank;
            } else {
                cmp = (int)deck->cards[j-1].suit - (int)key.suit;
            }
            if (cmp <= 0) break;
            deck->cards[j] = deck->cards[j-1];
            --j;
        }
        deck->cards[j] = key;
    }
}
