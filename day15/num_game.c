#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdint.h>

#define CAPACITY 1800000
#define BUCKET_SIZE 256

typedef struct {
    size_t occupied;
    uint32_t keys[BUCKET_SIZE];
    uint32_t values[BUCKET_SIZE];
} bucket;

typedef struct {
    size_t capacity;    
    bucket *buckets;
} hash_table;

unsigned int hash(uint32_t x)
{
    x = (x+0x7ed55d16) + (x<<12);
    x = (x^0xc761c23c) ^ (x>>19);
    x = (x+0x165667b1) + (x<<5);
    x = (x+0xd3a2646c) ^ (x<<9);
    x = (x+0xfd7046c5) + (x<<3);
    x = (x^0xb55a4f09) ^ (x>>16);

    return x;
}

hash_table *ht_init()
{
    hash_table *table = malloc(sizeof *table);
    table->capacity = CAPACITY;
    if (table == NULL) {
        fprintf(stderr, "Malloc failed!\n");
        exit(EXIT_FAILURE);
    }
    table->buckets = calloc(CAPACITY, sizeof *table->buckets);
    if (table->buckets == NULL) {
        fprintf(stderr, "Calloc failed with: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    for (uint32_t i = 0; i < CAPACITY; i++) {
        table->buckets[i].occupied = 0;
    }
    return table;
}

void ht_insert(hash_table *table, uint32_t key, uint32_t value)
{
    size_t bucket_id = hash(key) % CAPACITY;
    bucket *bucket = table->buckets + bucket_id;
    for (size_t i = 0; i < bucket->occupied; i++) {
        if (bucket->keys[i] == key) {
            bucket->values[i] = value;
            return;
        }
    }
    if (bucket->occupied == BUCKET_SIZE) {
        fprintf(stderr, "Bucket already full!\n");
        exit(EXIT_FAILURE);
    }
    bucket->keys[bucket->occupied] = key;
    bucket->values[bucket->occupied] = value;
    ++bucket->occupied;
}

uint32_t ht_get(hash_table *table, uint32_t key)
{
    size_t bucket_id = hash(key) % CAPACITY;
    bucket *bucket = table->buckets + bucket_id;
    for (size_t i = 0; i < bucket->occupied; i++) {
        if (bucket->keys[i] == key) {
            return bucket->values[i];
        }
    }
    return 0;
}

int main(void)
{
    const uint32_t numbers[] = {2, 20, 0, 4, 1, 17};
    hash_table *turns = ht_init();
    uint32_t last = 0;
    uint32_t diff = 0;
    size_t first = 0;

    uint32_t turn = 1;
    for (; turn <= 6; turn++) {
        ht_insert(turns, numbers[turn-1], turn);
        last = numbers[turn-1];
        first = 1;
    }
    // part 1
    // while (turn <= 2020)
    while (turn <= 30000000) {
        if (first) {
            if (ht_get(turns, 0) != 0 ) {
                diff = turn - ht_get(turns, 0);
                last = 0;
                first = 0;
                ht_insert(turns, 0, turn);
            } else {
                ht_insert(turns, 0, turn);
                last = 0;
                first = 1;
            }
            turn++;
            continue;
        } else {
            if (ht_get(turns, diff) != 0) {
                last = diff;
                first = 0;
                uint32_t tmp = diff;
                diff = turn - ht_get(turns, diff);
                ht_insert(turns, tmp, turn);
            } else {
                ht_insert(turns, diff, turn);
                last = diff;
                first = 1;
            }
            turn++;
        }
    }

    printf("Last number: %u\n", last);

    return 0;
} 
