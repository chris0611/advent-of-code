#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define BUFSIZE 512

int main(void) {
    char input_str[512];

    int num_valid = 0;

    int num_fields = 0;
    char *fields[] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};
    bool has_cid = false;

    while (fgets(input_str, BUFSIZE, stdin) != NULL) {

        int len = strlen(input_str);
        if (len != 1) {
            for (int i = 0; i < 8; i++) {
                if (strstr(input_str, fields[i]) != NULL) {
                    num_fields++;
                    if (i == 7)
                        has_cid = true;
                }
            }                

            if ((!has_cid && ((num_fields) == 7)) || (num_fields == 8)) {
                has_cid = false;
                num_fields = 0;
                num_valid++;
            }
        } else {
            num_fields = 0;
            has_cid = false;
        }
    }
    
    printf("(Part 1) Number of valid passports: %d\n", num_valid);;

    return 0;
}
