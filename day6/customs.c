#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#define CHARS 26
#define BUFSIZE 512

int main(void) {
    uint64_t score = 0;

    char group[BUFSIZE];
    uint16_t chars_read = 0;

    while (fgets(group, (BUFSIZE - chars_read), stdin) != NULL) {
        printf("%s", group);
    }
        

    return 0;
}
