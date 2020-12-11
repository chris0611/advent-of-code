CC=gcc
CFLAGS = -O3
DFLAGS = -g -Og -std=gnu99

.PHONY: debug

debug: seats.c
	$(CC) -o seats seats.c $(DFLAGS)

.PHONY: build

build: seats.c
	$(CC) -o seats seats.c $(CFLAGS)

clean:
	rm seats
