#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void move_p1(int amt, long *x, long *y, int deg)
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

void move_p2(int amt, long *x, long *y, long wp_x, long wp_y)
{
    //printf("Moving in the x-axis by: %ld\n", amt * wp_x);
    *x += amt * wp_x;
    //printf("Moving in the y-axis by: %ld\n", amt * wp_y);
    *y += amt * wp_y;
}

void rotate_wp(long *x, long *y, int deg)
{
    //printf("Rotating (%2ld,%2ld) by %d deg\n", *x, *y, deg);
    long tmp;
    switch(deg) {
        case 90:
            tmp = *x;
            *x = *y;
            *y = -tmp;
            break;

        case 180:
            *x = -(*x);
            *y = -(*y);
            break;

        case 270:
            tmp = *x;
            *x = -(*y);
            *y = tmp;
            break;

        default:
          fprintf(stderr, "Invalid number\n");
          exit(1);
          break;
    }
    //printf("Position after rotating: (%2ld,%2ld)\n", *x, *y);
}

int main(void)
{                   
    long x_1 = 0;   // east/west
    long y_1 = 0;   // north/south
    
    long x_2 = 0;   // same, but for part 2
    long y_2 = 0;

    long wp_x = 10; // waypoint position relative to ship
    long wp_y = 1;

    int deg = 90;   // degrees (0 facing directly north, going clockwise)

    char c;
    int d;

    while (scanf("%c%d\n", &c, &d) == 2) {
        switch(c) {
            case 'N':
                y_1 += d;
                wp_y += d;
                break;

            case 'S':
                y_1 -= d;
                wp_y -= d;
                break;

            case 'E':
                x_1 += d;
                wp_x += d;
                break;

            case 'W':
                x_1 -= d;
                wp_x -= d;
                break;

            case 'L':
                if (deg - d < 0)
                    deg = (deg - d + 360);
                else
                    deg -= d;
                rotate_wp(&wp_x, &wp_y, 360 - d);
                break;

            case 'R':
                if (deg + d >= 360)
                    deg = (deg+d - 360);
                else
                    deg += d;
                rotate_wp(&wp_x, &wp_y, d);
                break;

            case 'F':
                move_p1(d, &x_1, &y_1, deg);
                move_p2(d, &x_2, &y_2, wp_x, wp_y);
                break;

            default:
                fprintf(stderr, "Invalid input - '%c'\n", c);
                exit(1);
                break;
        }
        //printf("(%2ld,%2ld) facing %3d\n",x,y,deg);
    }

    printf("(Part 1) Manhattan distance is: %ld\n", (long)( abs( (double) x_1 ) + abs( (double) y_1 ) ));
    printf("(Part 2) Manhattan distance is: %ld\n", (long)( abs( (double) x_2 ) + abs( (double) y_2 ) ));

    return 0;
}
