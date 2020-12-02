#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 256

int main(void) {

    int valid_passes = 0;

    char *str = malloc(MAXLEN);
    char rule;
    int min = 0;
    int max = 0;

    while(scanf("%d-%d %c: %s\n", &min, &max, &rule, str) == 4) {
        printf("%d-%d %c: %s\n", min, max, rule, str);
    }

    return 0;
}
