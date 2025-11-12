# Simple Makefile for GCC/Clang builds (console)
CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2
INCLUDES := -Iinclude
SRC := src/card.c src/deck.c src/game.c main.c
OBJ := $(SRC:.c=.o)
BIN := card_game

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

test: $(BIN)
	$(CC) $(CFLAGS) $(INCLUDES) tests/test_main.c src/card.c src/deck.c -o test_runner
	./test_runner

clean:
	rm -f $(OBJ) $(BIN) test_runner

.PHONY: all clean test
