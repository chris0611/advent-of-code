#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#define BUFSIZE 256
#define MAXFIELDS 20

typedef struct {
    uint16_t min1;
    uint16_t max1;
    uint16_t min2;
    uint16_t max2;
} field;

int main(void)
{
    field fields[MAXFIELDS];

    for (uint8_t i = 0; i < MAXFIELDS; ++i) {
        fields[i].min1 = 0;
        fields[i].max1 = 0;
        fields[i].min2 = 0;
        fields[i].max2 = 0;
    }
    uint16_t a = 0, b = 0, c = 0, d = 0;

    uint8_t f_count = 0;
    char buffer[BUFSIZE] = {0};

    while (fgets(buffer, BUFSIZE, stdin) != NULL ) {
        if ((sscanf(buffer, "%*s %*s %hd-%hd or %hd-%hd\n", &a, &b, &c, &d) == 4) || 
            (sscanf(buffer, "%*s %hd-%hd or %hd-%hd\n", &a, &b, &c, &d) == 4)) {

            fields[f_count].min1 = a;
            fields[f_count].max1 = b;
            fields[f_count].min2 = c;
            fields[f_count].max2 = d;
            ++f_count;
        } else {
            break;
        }
    }

    // ignoring next few lines...
    for (uint8_t i = 0; i < 5; ++i) {
        if (scanf("%*s\n") != 0) exit(EXIT_FAILURE);
    }
    uint32_t errors = 0;
    uint8_t valid = 0;

    while ((fscanf(stdin, "%hd,", &a) == 1) || (fscanf(stdin, "%hd\n", &a) == 1)) {
        for (uint8_t i = 0; i < f_count; ++i) {
            if ((a >= fields[i].min1 && a <= fields[i].max1) || (a >= fields[i].min2 && a <= fields[i].max2)) {
                valid = 1;
                break;
            }
        }
        if (!valid) errors += a;
        valid = 0;
    }
    printf("(Part 1) Ticket scanning error rate: %u\n", errors);

    return 0;
}
