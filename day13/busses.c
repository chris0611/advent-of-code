#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#define BUFSIZE 32

int main(void)
{
    unsigned long earliest_time;

    if (scanf("%lu\n", &earliest_time) != 1) {
        fprintf(stderr, "Invalid input!\n");
        exit(1);
    }

    unsigned long *bus_ids = NULL;
    unsigned long *wait_times = NULL;
    unsigned int ids = 0;
    char ch;
    char str[BUFSIZE] = {0};
    unsigned int len = 0;

    while ((ch = getchar()) != EOF) {
        if (isdigit(ch)) {
            str[len] = ch;
            len++;
        } else {
            if (len > 0) {
                str[len] = '\0';
                ids++;
                if (bus_ids == NULL) {
                    bus_ids = malloc(sizeof(unsigned long));
                } else {
                    unsigned long *temp = realloc(bus_ids, sizeof(unsigned long) * ids);
                    if (temp == NULL) {
                        fprintf(stderr, "Realloc failed!\n");
                        exit(1);
                    }
                    bus_ids = temp;
                }
                bus_ids[ids-1] = atol(str);
                str[0] = '\0';
                len = 0;
            }
        }
    }
    wait_times = malloc(sizeof(unsigned long) * ids);
    unsigned long min_time = ULONG_MAX;
    unsigned int min_id = 0;

    for (int i = 0; i < ids; i++) {
        unsigned long time = 0;
        while (time < earliest_time) {
            time += bus_ids[i];
        }
        wait_times[i] = (time - earliest_time);
        if (wait_times[i] < min_time) {
            min_time = wait_times[i];
            min_id = i;
        }
    }

    printf("(Part 1) Product of earliest bus and its waiting time: %lu\n", wait_times[min_id] * bus_ids[min_id]);

    free(bus_ids);
    free(wait_times);
    return 0;
}
