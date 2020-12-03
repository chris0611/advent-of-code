#include <stdio.h>
#include <stdlib.h>
#define WIDTH 32
#define HEIGTH 323

int main(void) {
    
    int treecount = 0;

    int pos_x = 0, pos_y = 0;

    char **map = malloc(sizeof(char*)*HEIGTH);
    char ch;

    while ((ch = getchar()) != EOF) {
        if (map[pos_y] == NULL) {
            map[pos_y] = (char*)malloc(sizeof(char)*WIDTH);
        }
        if (ch == '\n') {
            printf("\n");
            pos_y++;
            pos_x = 0;
        } else {
            printf("%c", ch);
            map[pos_y][pos_x] = ch;
            pos_x++;
        }
    }

    return 0;
}
