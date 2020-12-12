#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void move(int amt, long *x, long *y, int deg)
{
    switch(deg) {
        case 0:
            *y += amt;
            break;    
        case 90:
            *x += amt;
            break;    
        case 180:
            *y -= amt;
            break;    
        case 270:
            *x -= amt;
            break;    
        default:
            fprintf(stderr, "Invalid direction\n");
            exit(1);
            break;
    }
}

int main(void)
{
    long x = 0;     // east/west
    long y = 0;     // north/south
    int deg = 90;   // direction (0 facing directly north, going clockwise)

    char c;
    int d;

    while (scanf("%c%d\n", &c, &d) == 2) {
        switch(c) {
            case 'N':
                y += d;
                break;
            case 'S':
                y -= d;
                break;
            case 'E':
                x += d;
                break;
            case 'W':
                x -= d;
                break;
            case 'L':
                if (deg - d < 0)
                    deg = (deg - d + 360);
                else
                    deg -= d;
                break;
            case 'R':
                if (deg + d >= 360)
                    deg = (deg+d - 360);
                else
                    deg += d;
                break;
            case 'F':
                move(d, &x, &y, deg);
                break;
            default:
                fprintf(stderr, "Invalid input - '%c'\n", c);
                exit(1);
                break;
        }
        //printf("(%2ld,%2ld) facing %3d\n",x,y,deg);
    }

    printf("(Part 1) Manhattan distance is: %ld\n", (long)( abs( (double) x ) + abs( (double) y ) ));

    return 0;
}
