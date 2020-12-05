#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 12
#define ROWS   127
#define COLUMNS  7


int main(void) {

    char b_pass[BUFSIZE];
    unsigned int max = 0;

    while (fgets(b_pass, BUFSIZE, stdin) != NULL) {
        unsigned int min_row = 0, max_row = ROWS;
        unsigned int min_col = 0, max_col = COLUMNS;

        int i = 0;
        while (b_pass[i] != '\n') {
            int row_range = max_row - min_row;
            int col_range = max_col - min_col;
            switch (b_pass[i]) {
                case 'F':
                    max_row = min_row + row_range/2;
                    break;
                case 'B':
                    min_row = max_row - row_range/2;
                    break;
                case 'L':
                    max_col = min_col + col_range/2;
                    break;
                case 'R':
                    min_col = max_col - col_range/2;
                    break;
                default:
                    break;
            }
            i++;
        }
        int id = max_row * 8 + max_col;
        if (id > max) max = id;
    }

    printf("(Part 1) Highest seat ID: %u\n", max);

    return 0; 
}
