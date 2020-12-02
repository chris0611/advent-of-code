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
        int occurences = 0;
        for (int i = 0; i < strlen(str); i++) {
            if (str[i] == rule)
                occurences++;
        }
        if (occurences >= min && occurences <= max)
            valid_passes++;
    }

    printf("%d\n", valid_passes);
    free(str);
    return 0;
}
