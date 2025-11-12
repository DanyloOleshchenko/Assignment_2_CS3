/**
 * @file main.c
 * @brief Entry point for the card game.
 */
#include "include/game.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t packs = 1;
    printf("Enter number of 52-card packs to use: ");
    if (scanf("%zu", &packs) != 1 || packs < 1) {
        fprintf(stderr, "Invalid input. Using 1 pack.\n");
        packs = 1;
    }
    return game_play(packs);
}
