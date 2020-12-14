CC = gcc
CFLAGS = -g -Og -std=gnu99 -Wall -pedantic -lm
FFLAGS = -O3 -Ofast -march=native -lm

mask: mask.c
	$(CC) -o mask mask.c $(CFLAGS)

.PHONY: fast

fast: mask.c
	$(CC) -o mask mask.c $(FFLAGS)

clean:
	rm mask
