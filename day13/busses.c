#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#define BUFSIZE 32

// returns x where (b_i * x) % m == 1
long long inverse_mod(long long b_i, long long m)
{
    long long m_0 = m, t, q;
    long long x0 = 0, x1 = 1;
    if (m == 1) return 1;
    while (b_i > 1) {
        q = b_i/m;
        t = m, m = b_i % m, b_i = t;
        t = x0, x0 = x1 - q * x0, x1 = t;
    }
    if (x1 < 0) x1 += m_0;
    return x1;
}

unsigned long long chinese_remainder(unsigned long long *n, unsigned int *a, unsigned int len)
{
    unsigned long long N = 1;
    unsigned long long sum = 0;
    long long b_i = 0;
    long long i;
    for (i = 0; i < len; i++) N *= n[i];

    for (i = 0; i < len; i++) {
        b_i = N/n[i];
        sum += (n[i] - (i + (long long)a[i])) * b_i * inverse_mod(b_i, n[i]);
    }

    return sum % N;
}

int main(void)
{
    unsigned long long earliest_time;

    if (scanf("%llu\n", &earliest_time) != 1) {
        fprintf(stderr, "Invalid input!\n");
        exit(1);
    }

    unsigned long long *bus_ids = NULL;
    unsigned long long *wait_times = NULL;
    unsigned int *xes = NULL;
    unsigned int num_x = 0;
    unsigned int ids = 0;
    char ch;
    char str[BUFSIZE] = {0};
    unsigned int len = 0;

    while ((ch = getchar()) != EOF) {
        if (isdigit(ch)) {
            str[len] = ch;
            len++;
        } else if (ch == 'x') {
            num_x++;
        } else {
            if (len > 0) {
                str[len] = '\0';
                ids++;
                if (bus_ids == NULL) {
                    bus_ids = malloc(sizeof(unsigned long long));
                    xes = malloc(sizeof(unsigned int));
                } else {
                    unsigned long long *temp = realloc(bus_ids, sizeof(unsigned long long) * ids);
                    unsigned int *xtemp = realloc(xes, sizeof(unsigned int) * ids);
                    if (temp == NULL || xtemp == NULL) {
                        fprintf(stderr, "Realloc failed!\n");
                        exit(1);
                    }
                    bus_ids = temp;
                    xes = xtemp;
                }
                bus_ids[ids-1] = atol(str);
                xes[ids-1] = num_x;
                str[0] = '\0';
                len = 0;
            }
        }
    }
    wait_times = malloc(sizeof(unsigned long long) * ids);
    unsigned long long min_time = ULLONG_MAX;
    unsigned int min_id = 0;

    for (int i = 0; i < ids; i++) {
        unsigned long long time = 0;
        while (time < earliest_time) {
            time += bus_ids[i];
        }
        wait_times[i] = (time - earliest_time);
        if (wait_times[i] < min_time) {
            min_time = wait_times[i];
            min_id = i;
        }
    }
    printf("(Part 1) Product of bus and time: %llu\n", wait_times[min_id] * bus_ids[min_id]);
    printf("(Part 2) Earliest starting time: %llu\n", chinese_remainder(bus_ids, xes, ids));       
            

    free(bus_ids);
    free(wait_times);
    free(xes);
    return 0;
}
