#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 256

int main(void) {

    int valid_passes = 0;

    char *str = malloc(MAXLEN);
    char rule;
    int min = 0;
    int max = 0;

    while(scanf("%d-%d %c: %s\n", &min, &max, &rule, str) == 4) {
        if (str[min-1] == rule || str[max-1] == rule) {
            if (str[min-1] != rule)
                valid_passes++;
            else if (str[max-1] != rule)
                valid_passes++;
        }
    }

    printf("%d\n", valid_passes);
    free(str);
    return 0;
}
