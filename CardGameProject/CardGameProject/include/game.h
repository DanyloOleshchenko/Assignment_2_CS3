/**
 * @file game.h
 * @brief Declarations for the two-player card game simulation.
 *
 * The game follows the rules described in the assignment brief:
 * - Two players receive 8 cards each from the hidden deck.
 * - Players must match the suit or rank of the top played card.
 * - If a player cannot play, they draw a card; drawn cards can only be used on the player's next turn.
 * - If the hidden deck becomes empty, the played pile is reshuffled into a new hidden deck, leaving the top card.
 */
#ifndef GAME_H
#define GAME_H

#include "deck.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Play a full game simulation with the given number of packs.
 * @param packs Number of 52-card packs to use (>=1).
 * @return 0 on success; non-zero on error.
 */
int game_play(size_t packs);

#ifdef __cplusplus
}
#endif

#endif /* GAME_H */
