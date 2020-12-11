#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define BUFSIZE 128
#define ROWS 10//91 
#define COLS 11//96 

void print_board(char **layout)
{
    for (int i = 0; i < ROWS; i++) {
        printf("%s\n", layout[i]);
    }
}

void free_2d(void **arr)
{
    for (int i = 0; i < ROWS; i++) {
        free(arr[i]);
    }
    free(arr);
}

unsigned int count_board(char **layout)
{
    unsigned int num = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (layout[i][j] == '#')
                num++;
        }
    }
    return num;
}

void reset_board(char **layout)
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (layout[i][j] == '#')
                layout[i][j] = 'L';
        }
    }
}



int check_neighbors(int row, int col, char **layout)
{
    if (layout[row][col] == '.')
        return 0;

    unsigned int num_nbrs = 0;

    for (int i = row-1; i <= row+1; i++) {
        if ((i < 0) || (i >= ROWS)) {
            continue;
        }
        for (int j = col-1; j <= col+1; j++) {
            if ((j < 0) || (j >= COLS)) {
                continue;
            }
            if (i == row && j == col) {
                continue;
            } 
            if (layout[i][j] == '#') {
                num_nbrs++;
            }
        }
    }

    return num_nbrs;
}

int update(char **layout, bool **updates)
{
    int updated_seats = 0;
    int nbrs = 0;
    int i;
    int j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            nbrs = check_neighbors(i, j, layout);
            if ((layout[i][j] == '#') && (nbrs >= 4)) {
                updates[i][j] = true;
            } else if ((layout[i][j] == 'L') && (nbrs == 0)) {
                updates[i][j] = true;
            }
        } 
    }    

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (updates[i][j]) {
                if (layout[i][j] == '#') {
                    layout[i][j] = 'L';
                } else {
                    layout[i][j] = '#';
                }
                updates[i][j] = false;
                updated_seats++;
            }
        }
    }

    return updated_seats;
}

int main(void)
{
    char **layout = malloc(ROWS * sizeof(char*));
    bool **updates = malloc(ROWS * sizeof(bool*));

    unsigned int i = 0;
    char buffer[BUFSIZE] = {0};

    while (fgets(buffer, COLS+1, stdin) != NULL) {
        layout[i] = malloc(sizeof(char) * COLS);
        updates[i] = calloc(COLS, sizeof(bool));
        buffer[COLS-1] = 0;

        if (strlen(buffer) != COLS-1) { // lazy way of checking input since the size is hardcoded
            fprintf(stderr, "Invalid # of columns inputted\nConsider changing COLS\n");
            exit(1);
        }
        strncpy(layout[i], buffer, COLS);
        i++;
    }

    while (update(layout, updates) != 0) {}
    printf("(Part 1) %d seats occupied\n", count_board(layout));
    reset_board(layout);
    print_board(layout);

    free_2d((void**)layout);
    free_2d((void**)updates);

    
    return 0;
}
