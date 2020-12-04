#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>

#define BUFSIZE 512
#define FIELDS 8

int main(void) {
    char input_str[512];

    int num_valid = 0;
    bool matched[FIELDS] = {0}; // to avoid matching same field more than once

    // regex for matching each field
    char *constraints[] = {
                           "byr:(19[2-9][0-9]|200[0-2])",                           // - for birth year 
                           "iyr:20(1[0-9]|20)",                                     // - for issue year 
                           "eyr:20(2[0-9]|30)",                                     // - for expiration year
                           "hgt:(1([5-8][0-9]|9[0-3])cm|(59|6[0-9]|7[0-6])in)",     // - for height
                           "hcl:#(([0-9])|([a-f])){6}",                             // - for hair color
                           "ecl:(amb|blu|brn|gry|grn|hzl|oth)",                     // - for eye color 
                           "pid:[0-9]{9}( |\n)",                                          // - for passport id
                           "cid:"                                                   // - for country id
                          };

    regex_t *regex = (regex_t*)malloc(sizeof(regex_t) * FIELDS);     // for storing compiled patterns 

    // compiling regex patterns
    for (int i = 0; i < FIELDS; i++) {
        if (regcomp(&regex[i], constraints[i], REG_EXTENDED) != 0) {
            fprintf(stderr, "Error during regex compilation\n");
            exit(1);
        } 
    }

    while (fgets(input_str, BUFSIZE, stdin) != NULL) {

        int len = strlen(input_str);
        if (len != 1) {
            for (int i = 0; i < FIELDS; i++) {
                if ((!matched[i]) && (regexec(&regex[i], input_str, 0, NULL, 0) != REG_NOMATCH)) {
                    matched[i] = true;
                }
            }                
        } else {
            for (int i = 0; i < FIELDS; i++) {
                matched[i] = false;
            }
        }
        if (matched[0] && matched[1] && matched[2] && matched[3] && matched[4] && matched[5] && matched[6]) {
            num_valid += 1;
            for (int i = 0; i < FIELDS; i++) {
                matched[i] = false;
            }
        }
    }
    printf("(Part 2) Number of valid passports: %d\n", num_valid);

    return 0;
}
