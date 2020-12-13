CC = gcc
CFLAGS = -O3 -Ofast -march=native
DFLAGS = -Wall -Werror -Og -g -std=gnu99

.PHONY: fast

fast: busses.c
	$(CC) -o busses busses.c $(CFLAGS)

.PHONY: debug

debug: busses.c
	$(CC) -o busses busses.c $(DFLAGS)

clean:
	rm busses
