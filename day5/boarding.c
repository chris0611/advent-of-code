#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFSIZE 12
#define ROWS   127
#define COLUMNS  7

int main(void) {

    char b_pass[BUFSIZE];
    unsigned int max_id = 0;
    unsigned int my_id = 0;
    bool seats[1024] = {0};

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
        seats[id] = true;
        if (id > max_id) max_id = id;
    }

    for (int i = 0; i <= ROWS; i++) {
        for (int j = 0; j <= COLUMNS; j++) {
            if (!seats[i*8+j]) {
                if (i != 0 && j != 0 && seats[i*8+j-1] && seats[i*8+j+1])
                    my_id = i*8+j;
            }
        }
    }

    printf("(Part 1) Highest seat ID: %u\n", max_id);
    printf("(Part 2) My seat ID: %u\n", my_id);

    return 0; 
}
