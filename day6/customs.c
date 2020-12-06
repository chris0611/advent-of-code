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

int count_same_answers(char *str, int len) {
    int counts[CHARS] = {0};
    int people = 0;
    int i, c = 0;

    for (i = 0; i < len; i++) {
        if (str[i] >= 97 && str[i] <= 122) {
            counts[str[i]-97] += 1;
        } else if (str[i] == 10) {
            people++;
        }
    }
    for (i = 0; i < CHARS; i++) {
        if ((counts[i] > 0 && people > 1) && (counts[i] % people == 0)) {
            c += 1;
        } else if (people == 1) {
            if (counts[i] > 0)
              c += 1;
        }
    }
    //printf("Input string:\n%s", str);
    //printf("People: %d\n", people);
    //printf("Returning: %d\n\n", c);
    return c;
}

int main(void) {
    unsigned long sum_pt1 = 0;
    unsigned long sum_pt2 = 0;

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
            sum_pt1 += count_unique_char(group, strlen(group));
            sum_pt2 += count_same_answers(group, strlen(group));
            strcpy(group, "\0");
        }
    }
    sum_pt1 += count_unique_char(group, strlen(group));
    sum_pt2 += count_same_answers(group, strlen(group));

    printf("(Part 1) Sum of counts: %ld\n", sum_pt1);
    printf("(Part 2) Sum of counts: %ld\n", sum_pt2);

    return 0;
}
