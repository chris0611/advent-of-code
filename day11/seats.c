#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

#define BUFSIZE 128
#define ROWS 91 //10
#define COLS 96 //11

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

// takes in one of 8 directions to search in 
int recur_neighbors(int r_d, int c_d, int row, int col, char **layout)
{
    unsigned int num_nbrs = 0;

    if (r_d == INT_MAX) {
        if (layout[row][col] == '.') {
            return 0;
        }
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
                } else if (layout[i][j] != 'L') {
                    int row_dir = i - row;
                    int col_dir = j - col;
                    num_nbrs += recur_neighbors(row_dir, col_dir, i, j, layout);
                }
            }
        }
    } else {
        if (row+r_d < 0 || row+r_d >= ROWS || col+c_d < 0 || col+c_d >= COLS) {
            return 0;
        } else {
            if (layout[row+r_d][col+c_d] == '#') {
                return 1;
            } else if (layout[row+r_d][col+c_d] == 'L') {
                return 0;
            } else {
                return recur_neighbors(r_d, c_d, row+r_d, col+c_d, layout);   
            }
        }
    }
    return num_nbrs;
}

int update(char **layout, bool **updates, bool part1)
{
    int updated_seats = 0;
    int nbrs = 0;
    int max_nbrs = 5;
    int i;
    int j;

    if (part1)
        max_nbrs = 4;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (part1) {
                nbrs = check_neighbors(i, j, layout);
            } else {
                nbrs = recur_neighbors(INT_MAX, INT_MAX, i, j, layout);
            }
            if ((layout[i][j] == '#') && (nbrs >= max_nbrs)) {
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




    clock_t start, end, sum1, sum2;
    unsigned int N = 10000;
    double avg_1, avg_2; 

    sum1 = 0;

    for (int n = 0; n < N; n++) {
        start = clock();
        while (update(layout, updates, true) != 0) {}
        end = clock();
        sum1 += end - start;
        reset_board(layout);
    }

    avg_1 = ((((double)(sum1))/CLOCKS_PER_SEC)*(1000.0))/(double)N;

    while (update(layout, updates, true) != 0) {}
    printf("(Part 1) %d seats occupied\n", count_board(layout));

    printf("Average time: %2.3f ms\n", avg_1);
    
    reset_board(layout);
    sum2 = 0;
    
    for (int n = 0; n < N; n++) {
        start = clock();
        while (update(layout, updates, false) != 0) {}
        end = clock();
        sum2 += end - start;
        reset_board(layout);
    }

    avg_2 = ((((double)(sum2))/CLOCKS_PER_SEC)*(1000.0))/(double)N;

    while (update(layout, updates, false) != 0) {}
    printf("(Part 2) %d seats occupied\n", count_board(layout));
    printf("Average time: %2.3f ms\n", avg_2);

    free_2d((void**)layout);
    free_2d((void**)updates);

    
    return 0;
}
