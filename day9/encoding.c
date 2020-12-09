#include <stdio.h>
#include <stdbool.h>

#define P_SIZE 25    // size of the preamble
#define MAXSIZE 1024

bool search(unsigned long *numbers, unsigned int length, unsigned long n)
{
    for (int i = 0; i < length; i++) {
        for (int j = i; j < length; j++) {
            if ((numbers[i] + numbers[j]) == n)
                return true;
        }
    } 
    return false;
}

unsigned long max_list(const unsigned long *list, const unsigned int len)
{
    unsigned long max = list[0];

    for (int i = 1; i < len; i++) {
        if (list[i] > max)
            max = list[i];
    }
    //printf("Max is %lu\n", max);
    return max;
}

unsigned long min_list(const unsigned long *list, const unsigned int len)
{
    unsigned long min = list[0];

    for (int i = 1; i < len; i++) {
        if (list[i] < min)
            min = list[i];
    }
    //printf("Min is %lu\n", min);
    return min;
} 

unsigned long search_list(unsigned long *list, unsigned long num)
{
    // Function searches for contigous list with sum equal to num
    unsigned long set[MAXSIZE] = {0};   // our set
    unsigned int set_len = 0;       // must be > 1

    for (int i = 0; i < MAXSIZE; i++) {
        int sum = 0;
        for (int j = i; j < MAXSIZE; j++) {
            set[set_len] = list[j];
            set_len++;
            sum += list[j];
            if (sum == num && set_len > 1) {
                unsigned long max = max_list(set, set_len);
                unsigned long min = min_list(set, set_len);
                return max + min;
            } else if (sum > num) {
                for (int k = 0; k < set_len; k++) {
                    set[k] = 0;
                }
                set_len = 0;
                break;
            }
        }
    }
    return 0;
}

int main(void)
{
    unsigned long preamble[P_SIZE];
    unsigned long numbers[MAXSIZE] = {0}; // too lazy to dynamically allocate memory xd
    unsigned int counter = 0;

    // read in initial preamble
    while (counter < P_SIZE) {
        unsigned long tmp = 0;
        scanf("%lu\n", &tmp);
        preamble[counter] = tmp;
        numbers[counter] = tmp;
        counter++;
    }
    unsigned long num = 0;
    unsigned long invalid = 0;
    bool found = false;

    while (scanf("%lu\n", &num) == 1) {
        if (!found && !search(preamble, P_SIZE, num)) {
            invalid = num;
            found = true;
        }
        preamble[counter % P_SIZE] = num;
        numbers[counter] = num;
        counter++;    
    }
    printf("(Part 1) sum: %lu\n", invalid);
    printf("(Part 2) sum: %lu\n", search_list(numbers, invalid));

    return 0;
}
