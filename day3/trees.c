#include <stdio.h>
#include <stdlib.h>
#define WIDTH 32
#define HEIGHT 323

int main(void) {
    
    int treecount = 0;

    int pos_x = 0, pos_y = 0;

    char **map = malloc(sizeof(char*)*HEIGHT);
    char ch;

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

    pos_x = 0;

    for (pos_y = 0; pos_y < HEIGHT; pos_y++) {
        char pos = map[pos_y][pos_x%(WIDTH-1)];
        // printf("Position (%d,%d) has: %c\n", pos_x, pos_y, pos);
        if (pos == '#')
            treecount++;  
        pos_x += 3;
    }    
    printf("Trees encountered: %d\n", treecount);
    return 0;
}
