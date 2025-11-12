/**
 * @file card.h
 * @brief Declarations for the Card data type and card-level utilities.
 *
 * This header defines the user-defined data type @c Card for a standard 52-card deck,
 * along with @c Suit and @c Rank enumerations and basic helper functions.
 *
 * The design is intentionally generic so it can be reused for other card games.
 */
#ifndef CARD_H
#define CARD_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumeration of the four suits in a standard deck.
 */
typedef enum {
    SUIT_CLUB = 0,
    SUIT_SPADE = 1,
    SUIT_HEART = 2,
    SUIT_DIAMOND = 3
} Suit;

/**
 * @brief Enumeration of the ranks in a standard deck.
 */
typedef enum {
    RANK_TWO = 2,
    RANK_THREE,
    RANK_FOUR,
    RANK_FIVE,
    RANK_SIX,
    RANK_SEVEN,
    RANK_EIGHT,
    RANK_NINE,
    RANK_TEN,
    RANK_JACK,
    RANK_QUeen,
    RANK_KING,
    RANK_ACE
} Rank;

/**
 * @brief Struct representing a single playing card.
 */
typedef struct {
    Suit suit;  /**< Suit of the card. */
    Rank rank;  /**< Rank of the card. */
} Card;

/**
 * @brief Print a card to stdout in a compact human-readable format (e.g., "5♠").
 * @param c The card to print.
 */
void print_card(Card c);

/**
 * @brief Compare two cards by rank then suit.
 * @param a First card.
 * @param b Second card.
 * @return Negative if a<b, 0 if equal, positive if a>b.
 */
int compare_cards(Card a, Card b);

#ifdef __cplusplus
}
#endif

#endif /* CARD_H */
