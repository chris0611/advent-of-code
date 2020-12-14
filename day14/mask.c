#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <assert.h>

#define WIDTH 36
#define BUFSIZE 128
#define MEMSIZE 1024

void bin(uint64_t n)
{
    uint64_t i;
    for (i = 1ull << 63ull; i > 0ull; i = i / 2ull)
        (n & i) ? printf("1") : printf("0");
}

// Returns addresses masked with all possible masks, sets len to amount of addresses returned
uint64_t *possible_addr(uint64_t address, uint8_t *mask, uint32_t *len)
{
    uint64_t *addresses = NULL;
    uint8_t **masks = NULL;
    uint8_t *tmp_mask = malloc(sizeof(uint8_t) * WIDTH);

    uint16_t floats = 0;
    uint16_t index;

    // sum floats in the given mask
    for (uint32_t i = 0; i < 36; i++) {
        if (mask[i] == 'X') floats++;
    }

    // amt of possible masks is equal to 2^(floats in mask)
    // example: Mask has 6 floats, so there are 2^6 = 64 possible masks
    *len = (uint32_t)exp2((double)floats);
    masks = (uint8_t**)malloc(sizeof(uint8_t*) * (*len));
    addresses = malloc(sizeof(uint64_t) * (*len));

    for (index = 0; index < *len; index++) {
        strncpy((char*)tmp_mask, (char*)mask, WIDTH);
        uint32_t i;
        for (i = 1u; i < (1u << 15u); i *= 2) { 
            for (uint32_t j = WIDTH-1; j >= 0; j--) {
                if (tmp_mask[j] == 'X') {
                    if (index & i) {
                        tmp_mask[j] = '1';
                        break;
                    } else {
                        tmp_mask[j] = '0'; 
                        break;
                    }
                } else if (j == 0) break;
            }
        }
        masks[index] = malloc(sizeof(uint8_t) * WIDTH);
        strncpy((char*)masks[index], (char*)tmp_mask, WIDTH);
    }
    free(tmp_mask);
    
    for (index = 0; index < *len; index++) {
        addresses[index] = address;
        for (uint64_t j = 0u; j < WIDTH; j++) {
            if (mask[j] == 'X') {
                if (masks[index][j] == '1') {
                    addresses[index] |= 1ull << (35-j);
                } else if (masks[index][j] == '0') {
                    addresses[index] &= ~(1ull << (35-j));
                }  
            } else if (mask[j] == '1') {
                addresses[index] |= 1ull << (35-j);
            }
        }
        free(masks[index]);
    }

    free(masks);
    return addresses;
}

typedef struct memory {
    uint64_t address;
    uint64_t value;
} memory;

int main(void)
{
    uint8_t mask[WIDTH] = {0};
    uint64_t sum = 0;
    uint64_t sum2 = 0;
    
    memory *mem_buf1[MEMSIZE] = {0};
    memory **mem_buf2 = NULL;
    uint32_t entries1 = 0;
    uint64_t entries2 = 0;
    
    char buf[BUFSIZE] = {0};
    uint64_t address = 0;
    uint64_t value = 0;
    
    while (fgets(buf, BUFSIZE, stdin) != NULL) {
        if (sscanf(buf, "mask = %[X01]", buf) == 1) {
            uint32_t i;
            for (i = 0; i < strlen(buf); i++) {
                mask[i] = buf[i];
            }
        } else if (sscanf(buf, "mem[%lu] = %lu\n", &address, &value) == 2) {

            
            uint32_t i;
            uint32_t num = 0;
            uint64_t *addr = NULL;
            bool addr_exists2 = false;
            addr = possible_addr(address, mask, &num);

            // Part 2 stuff
            if (mem_buf2 == NULL) {
                mem_buf2 = malloc(sizeof(memory*) * num);
            } else {
                memory **temp = realloc(mem_buf2, ((sizeof(memory*) * num) + (sizeof(memory*) * entries2)));
                assert(temp != NULL);
                mem_buf2 = temp;
            }
            
            for (i = 0; i < num; i++) {
                addr_exists2 = false;
                for (uint32_t j = 0; j < entries2; j++) {
                    if ((mem_buf2[j]->address) == addr[i]) {
                        mem_buf2[j]->value = value;
                        addr_exists2 = true;
                        break;
                    }
                }
                if (!addr_exists2) {
                    memory *n = NULL;
                    n = malloc(sizeof(memory));
                    assert(n != NULL);
                    n->address = addr[i];
                    n->value = value;
                    mem_buf2[entries2] = n;
                    entries2++;
                }
            }
            free(addr);
    
            // Part 1 stuff
            for (i = 0; i < WIDTH; i++) {
                if (mask[i] == '1') {
                    value |= 1ull << (35-i);
                } else if (mask[i] == '0') {
                    value &= ~(1ull << (35-i));
                }
            }

            bool addr_exists1 = false;

            for (i = 0; i < entries1; i++) {
                if (mem_buf1[i]->address == address) {
                    mem_buf1[i]->value = value;
                    addr_exists1 = true;
                    break;
                }
            }
            if (!addr_exists1) {
                memory *new = malloc(sizeof(memory));
                new->address = address;
                new->value = value;
                mem_buf1[entries1] = new;
                entries1++;
            }
        }
    }
    for (uint32_t i = 0; i < entries1; i++) {
        sum += mem_buf1[i]->value;
        free(mem_buf1[i]);
    }
    for (uint64_t i = 0; i < entries2; i++) {
        sum2 += mem_buf2[i]->value;
        free(mem_buf2[i]);
    }
    free(mem_buf2);
    printf("(Part 1) Sum: %lu\n", sum);
    printf("(Part 2) Sum: %lu\n", sum2);
    return 0;
}
