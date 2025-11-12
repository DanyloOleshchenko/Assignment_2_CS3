/**
 * @file deck.h
 * @brief Declarations for the CardDeck data type and deck-level operations.
 *
 * CardDeck is a dynamically-sized collection of @c Card elements that supports
 * adding/removing cards, shuffling, and sorting. Dynamic memory is used to
 * support any number of complete 52-card packs.
 */
#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Dynamic deck of cards backed by a resizable array.
 */
typedef struct {
    Card *cards;   /**< Pointer to contiguous storage of cards. */
    size_t size;   /**< Current number of cards in the deck. */
    size_t capacity; /**< Allocated capacity of the deck. */
} CardDeck;

/**
 * @brief Create an empty deck with an initial capacity.
 * @param initial_capacity Initial allocation size (can be 0).
 * @return Pointer to a newly allocated deck, or NULL on failure.
 */
CardDeck* deck_create(size_t initial_capacity);

/**
 * @brief Free a deck and all associated memory.
 * @param deck Pointer to the deck to free (can be NULL).
 */
void deck_free(CardDeck *deck);

/**
 * @brief Ensure the deck has capacity for at least @p needed cards.
 * @param deck The deck.
 * @param needed Minimum required capacity.
 * @return 0 on success, non-zero on allocation failure.
 */
int deck_reserve(CardDeck *deck, size_t needed);

/**
 * @brief Push a card onto the top of the deck.
 * @param deck The deck.
 * @param c The card to add.
 * @return 0 on success, non-zero on allocation failure.
 */
int deck_push(CardDeck *deck, Card c);

/**
 * @brief Pop a card from the top of the deck.
 * @param deck The deck.
 * @param out Pointer to store the removed card (can be NULL to discard).
 * @return 0 on success, non-zero if the deck is empty.
 */
int deck_pop(CardDeck *deck, Card *out);

/**
 * @brief Remove a card at a given index (0 is top). Shifts subsequent cards down.
 * @param deck The deck.
 * @param index Zero-based index (0 <= index < size).
 * @param out Optional pointer to store removed card.
 * @return 0 on success, non-zero on invalid index.
 */
int deck_remove_at(CardDeck *deck, size_t index, Card *out);

/**
 * @brief Insert a card at a given index (0 is top).
 * @param deck The deck.
 * @param index Zero-based index (0 <= index <= size).
 * @param c The card to insert.
 * @return 0 on success, non-zero on allocation failure or bad index.
 */
int deck_insert_at(CardDeck *deck, size_t index, Card c);

/**
 * @brief Initialize a deck with M full 52-card packs in order.
 * @param deck Target deck (must exist and be empty or will be cleared).
 * @param packs Number of complete packs (M >= 1).
 * @return 0 on success, non-zero on allocation failure or bad arg.
 */
int deck_init_standard_packs(CardDeck *deck, size_t packs);

/**
 * @brief Shuffle the deck using the algorithm from the assignment brief.
 * @param source Source deck (will be consumed/emptied).
 * @param dest Destination deck (will be overwritten).

 * @return 0 on success, non-zero on error.
 */
int deck_shuffle_to(const CardDeck *source, CardDeck *dest);

/**
 * @brief In-place shuffle convenience wrapper (allocates a temp deck).
 * @param deck The deck to shuffle in place.
 * @return 0 on success, non-zero on allocation failure.
 */
int deck_shuffle(CardDeck *deck);

/**
 * @brief Sort the deck by rank then suit using a chosen algorithm.
 * @param deck The deck to sort.
 */
void deck_sort(CardDeck *deck);

#ifdef __cplusplus
}
#endif

#endif /* DECK_H */
