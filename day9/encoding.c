#include <stdio.h>
#include <stdbool.h>

#define P_SIZE 25    // size of the preamble

bool search(unsigned long numbers[], unsigned long n)
{
    for (int i = 0; i < P_SIZE; i++) {
        for (int j = i; j < P_SIZE; j++) {
            if (numbers[i] + numbers[j] == n)
                return true;
        }
    } 
    return false;
}


int main(void)
{
    unsigned long numbers[P_SIZE];
    unsigned int counter = 0;

    // read in initial preamble
    while (counter < P_SIZE) {
        scanf("%lu\n", &numbers[counter]);
        counter++;
    }
    unsigned long num = 0;

    while (scanf("%lu\n", &num) != 0) {
        if (!search(numbers, num)) {
            break;
        }
        numbers[counter % P_SIZE] = num;
        counter++;    
    }
    printf("(Part 1) the first number that doesn't fit is: %lu\n", num);

    return 0;
}
