CC = gcc
CFLAGS = -Wall -Og -g -std=gnu99 -pedantic
FFLAGS = -O3 -Ofast -march=native

.PHONY: fast

fast: num_game.c
	$(CC) -o num_game num_game.c $(FFLAGS)

.PHONY: debug

debug: num_game.c
	$(CC) -o num_game num_game.c $(CFLAGS)

clean:
	rm num_game
