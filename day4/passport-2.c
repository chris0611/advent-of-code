#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>
#include <sys/types.h>

#define BUFSIZE 512

int main(void) {
    char input_str[512];

    int num_valid = 0;
    int num_valid_pt2 = 0;

    int num_fields = 0;
    int num_fields_pt2 = 0;

    char *fields[] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};
    bool matched[8] = {0}; // to avoid matching same field more than once

    // regex for matching each field
    char *constraints[] = {
                           "byr:(19[2-9][0-9]|200[0-2])",                           // - for birth year 
                           "iyr:20(1[0-9]|20)",                                     // - for issue year 
                           "eyr:20(2[0-9]|30)",                                     // - for expiration year
                           "hgt:(1([5-8][0-9]|9[0-3])cm|(59|6[0-9]|7[0-6])in)",     // - for height
                           "hcl:#(([0-9])|([a-f])){6}",                             // - for hair color
                           "ecl:(amb|blu|brn|gry|grn|hzl|oth)",                     // - for eye color 
                           "pid:[0-9]{9}",                                          // - for passport id
                           "cid:."                                                  // - for country id
                          };

    regex_t *regex = (regex_t*)malloc(sizeof(regex_t) * 8);     // storing compiled patterns 

    // compiling regex patterns
    for (int i = 0; i < 8; i++) {
        if (regcomp(&regex[i], constraints[i], REG_EXTENDED) != 0) {
            fprintf(stderr, "Error during regex compilation\n");
            exit(1);
        } 
    }

    while (fgets(input_str, BUFSIZE, stdin) != NULL) {

        int len = strlen(input_str);
        if (len != 1) {
            for (int i = 0; i < 8; i++) {
                if (strstr(input_str, fields[i]) != NULL) {
                    num_fields++;
                    if (i == 7)
                        matched[i] = true; // cid doesn't matter
                }
                if (!matched[i] && regexec(&regex[i], input_str, 0, NULL, 0) != REG_NOMATCH) {
                    matched[i] = true;
                    num_fields_pt2++;
                }
            }                

            if ((!matched[7] && ((num_fields) == 7)) || (num_fields == 8)) {
                for (int i = 0; i < 8; i++) {
                    matched[i] = false;
                }
                num_fields = 0;
                num_valid++;
            }
            if (num_fields_pt2 == 8 || (!matched[7] && num_fields_pt2 == 7)) {
                for (int i = 0; i < 8; i++) {
                    matched[i] = false;
                }
                num_fields_pt2 = 0;
                num_valid_pt2++;

            }
        } else {
            num_fields = 0;
            num_fields_pt2 = 0;
            for (int i = 0; i < 8; i++) {
                matched[i] = false;  
            }
        }
    }
    
    printf("(Part 1) Number of valid passports: %d\n", num_valid);
    printf("(Part 2) Number of valid passports: %d\n", num_valid_pt2);

    return 0;
}
