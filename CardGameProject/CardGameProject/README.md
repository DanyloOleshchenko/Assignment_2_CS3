# CE4703 Assignment 2 — Group 16 (4-Member Setup)

Console implementation of a two-player card game with user-defined data types (`Card`, `CardDeck`) and dynamic data structures. Code follows K&R style and is documented with Doxygen.

## Project Structure

```text
CardGameProject/
├─ include/
│  ├─ card.h        # Card, Suit, Rank, and card utilities
│  ├─ deck.h        # CardDeck and deck operations (dynamic memory)
│  └─ game.h        # Game orchestration API
├─ src/
│  ├─ card.c
│  ├─ deck.c
│  └─ game.c
├─ main.c           # Entry point
├─ tests/
│  └─ test_main.c   # Optional sanity tests
├─ Makefile         # GCC/Clang build (optional if using Visual Studio)
├─ .gitignore
└─ Doxyfile         # Doxygen configuration (sample)
```

## Build & Run (GCC/Clang)

```bash
make
./card_game
```

Or run tests:

```bash
make test
```

## Build (Visual Studio Community, Windows)

1. Create a new **Console Application** solution.
2. Add existing files from `include/` and `src/` plus `main.c` to the project.
3. In **C/C++ → General → Additional Include Directories**, add `$(ProjectDir)include`.
4. Ensure **Language Standard** is C11 (or latest).
5. Build and run.

## Game Rules (Summary)

- Use `M` packs of 52 cards (user input).
- Deal 8 cards to each player, alternating.
- Reveal the top card to start the played pile.
- On a turn, a player must play a card that matches by **suit or rank**; otherwise they draw one card and skip playing it until their next turn.
- If the hidden deck becomes empty, reshuffle the played pile (keeping the current top card).
- The first player to empty their hand wins.

## Team Responsibilities (4 Members)

- **Member 1 — Core Setup & Build (Team Lead / Integrator)**  
  - Create repo structure, configure build (Makefile or VS project), set CI/checks if any, and review/merge PRs.  
  - Owns `main.c`, ensures end-to-end build runs.  
  - Final packaging (ZIP) with generated Doxygen docs.

- **Member 2 — Card & Basic Operations**  
  - Implement `card.h/.c`: enums (`Suit`, `Rank`), `Card` struct, `print_card`, `compare_cards`.  
  - Unit sanity tests in `tests/test_main.c`.

- **Member 3 — Dynamic Deck & Algorithms**  
  - Implement `deck.h/.c`: dynamic array, `deck_push/pop/insert/remove`, `deck_init_standard_packs`, `deck_shuffle`, `deck_sort`.  
  - Ensure no leaks (balanced `malloc/free`).  

- **Member 4 — Game Logic & Integration**  
  - Implement `game.h/.c`: dealing, turn loop, matching logic, reshuffle when hidden is empty, text I/O.  
  - Works with Member 3 to ensure API usage is correct.

> Everyone: follow K&R style, write Doxygen comments, and avoid globals/goto.

## Doxygen

To generate docs (if Doxygen is installed):

```bash
doxygen Doxyfile
```

Output will appear under `doc/html/`.

## Notes

- Dynamic memory is required; fixed-size arrays for `CardDeck` are **not** allowed.
- Sorting: the template uses **insertion sort** for clarity; you may replace it with any algorithm discussed in lectures if preferred.
- Keep console I/O minimal and clear.
