#include <stdio.h>
#include <string.h>

#define CHARS 26
#define BUFSIZE 512

int count_unique_char(char *str, int len) {
    int hash[CHARS] = {0};
    int i, c = 0;
    
    for (i = 0; i < len; i++) {
        if (str[i] >= 97 && str[i] <= 122)
            hash[str[i]-97] = 1;
    }

    for (i = 0; i < CHARS; i++) {
        c += hash[i];
    }
    return c;
}

int main(void) {
    unsigned long score = 0;

    char buffer[BUFSIZE] = {0};
    char group[BUFSIZE] = {0};

    while (fgets(buffer, BUFSIZE, stdin) != NULL) {
        // count 
        int len_buff = strlen(buffer);

        if (len_buff > 1) {
            if (strlen(group) == 0) {
                strcpy(group, buffer);
            } else {
                strcat(group, buffer);
            }
        } else {
            score += count_unique_char(group, strlen(group));
            strcpy(group, "\0\0");
        }
    }
    score += count_unique_char(group, strlen(group));

    printf("(Part 1) Sum of counts: %ld\n", score);

    return 0;
}
