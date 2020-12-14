#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define WIDTH 36
#define BUFSIZE 128
#define MEMSIZE 1024

void bin(uint64_t n)
{
    uint64_t i;
    for (i = 1ull << 63ull; i > 0ull; i = i / 2ull)
        (n & i) ? printf("1") : printf("0");
}

typedef struct memory {
    uint32_t address;
    uint64_t value;
} memory;

int main(void)
{
    uint8_t mask[WIDTH] = {0};
    uint64_t sum = 0;
    
    memory *mem_buf[MEMSIZE] = {0};
    uint32_t entries = 0;
    
    char buf[BUFSIZE] = {0};
    uint32_t address = 0;
    uint64_t value = 0;
    
    while (fgets(buf, BUFSIZE, stdin) != NULL) {
        if (sscanf(buf, "mask = %[X01]", buf) == 1) {
            uint32_t i;
            /*printf("\nMask:\n");
            for (i = 0; i < 28; i++) {
                printf("X");
            }*/
            for (i = 0; i < strlen(buf); i++) {
                mask[i] = buf[i];
                //printf("%c", mask[i]);
            }
            //printf("\n\n");
        } else if (sscanf(buf, "mem[%u] = %lu\n", &address, &value) == 2) {

            uint32_t i;
    
            /*
            printf("Before mask:\n");
            bin(value);
            printf("\n");
            */

            for (i = 0; i < 36; i++) {
                if (mask[i] == '1') {
                    value |= 1ull << (35-i);
                } else if (mask[i] == '0') {
                    value &= ~(1ull << (35-i));
                }
            }

            /*
            printf("After mask:\n");
            bin(value);
            printf("\n\n");
            */

            bool addr_exists = false;

            for (i = 0; i < entries; i++) {
                if (mem_buf[i]->address == address) {
                    mem_buf[i]->value = value;
                    //printf("Overwrote address %u\n", address);
                    addr_exists = true;
                    break;
                }
            }
            if (!addr_exists) {
                memory *new = malloc(sizeof(memory));
                new->address = address;
                new->value = value;
                mem_buf[entries] = new;
                entries++;
            }
        }
    }
    for (uint32_t i = 0; i < entries; i++) {
        sum += mem_buf[i]->value;
        free(mem_buf[i]);
    }
    printf("(Part 1) Sum: %lu\n", sum);
    return 0;
}
