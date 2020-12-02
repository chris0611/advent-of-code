#include <stdio.h>
#define MAXSIZE 1024


int main(void) {
    int input_array[MAXSIZE];

    int i = 0;

    while (scanf("%d\n", &input_array[i]) == 1 && i < MAXSIZE) {i++;}
    int len = i;

    for (i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            if (input_array[i] + input_array[j] == 2020) {
                printf("%d\n", input_array[i] * input_array[j]);
                break; 
            }
        }
    } 

    return 0;
}
