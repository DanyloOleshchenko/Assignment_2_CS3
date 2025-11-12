/**
 * @file test_game.c
 * @brief Smoke test for the full game (runs a single game and exits).
 */
#include "common.h"
#include "../include/game.h"

int main(void)
{
    /* Should run to completion with 1 pack. */
    int rc = game_play(1);
    ASSERT_EQ_INT(0, rc);
    return 0;
}
