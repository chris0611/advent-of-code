#include <stdio.h>
#include <stdlib.h>
#define WIDTH 32
#define HEIGHT 323

int main(void) {
    
    int pos_x = 0, pos_y = 0;

    char **map = malloc(sizeof(char*)*HEIGHT);
    char ch;

    long long counts[5] = {0};
    int slope_x[] = {1, 3, 5, 7, 1};
    int slope_y[] = {1, 1, 1, 1, 2};

    // while-loop reads map into 2D array
    //
    while ((ch = getchar()) != EOF) {
        if (map[pos_y] == NULL) {
            map[pos_y] = (char*)malloc(sizeof(char)*WIDTH);
        }
        if (ch == '\n') {
            pos_y++;
            pos_x = 0;
        } else {
            map[pos_y][pos_x] = ch;
            pos_x++;
        }
    }

    for (int i = 0; i < 5; i++) {
        pos_x = 0;
        for (pos_y = 0; pos_y < HEIGHT; pos_y += slope_y[i]) {
            char pos = map[pos_y][pos_x%(WIDTH-1)];
            // printf("Position (%d,%d) has: %c\n", pos_x, pos_y, pos);
            if (pos == '#')
                counts[i]++;  
            pos_x += slope_x[i];
        }
    }
    printf("(Part 1) Trees encountered: %d\n", counts[1]);
    
    long long product = counts[0] * counts[1] * counts[2] * counts[3] * counts[4];

    printf("(Part 2 Products of trees: %lld\n", product);

    return 0;
}
