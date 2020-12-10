#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXLEN 128

int cmpfunc(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

int main(void)
{
    unsigned int arr[MAXLEN] = {0};
    unsigned int length = 0;
    while (scanf("%d\n", &arr[length]) == 1) length++;

    qsort(arr, length, sizeof(unsigned int), cmpfunc);

    unsigned int one_jolt = 0;
    unsigned int two_jolts = 0;
    unsigned int three_jolts = 0;
    unsigned int product;

    int step = 0;

    for (int i = 0; i < length; i++) {
        int diff = arr[i] - step;

        if (diff == 1) {
            one_jolt++;
        } else if (diff == 2) {
            two_jolts++;
        } else if (diff == 3) {
            three_jolts++;
        }
        step = arr[i]; 
    }
    three_jolts++; // device always has 3 jolt difference
    
    unsigned long long paths = 0;
    unsigned long long sums[MAXLEN] = {0};
    sums[length-1] = 1;

    for (int i = length-2; i >= 0; i--) {
        unsigned long long partial_sum = 0;

        partial_sum += sums[i+1];

        
        if (i+3 < length) {
            if (arr[i+3] - arr[i] == 3)
                partial_sum += sums[i+3];
            if (arr[i+2] - arr[i] <= 3)
                partial_sum += sums[i+2];
        } else if (i+2 < length) {
            if (arr[i+2] - arr[i] <= 3)
                partial_sum += sums[i+2];
        }
        //printf("%2d: Sum: %lld\n", arr[i], partial_sum);
        sums[i] = partial_sum;
    }
    for (int i = 2; i >= 0; i--) {
        //printf("Array %d = %d\n", i, arr[i]);
        if (arr[i] == 3) {
            paths += sums[i]; 
        } else if (arr[i] == 2) {
            paths += sums[i]; 
        } else if (arr[i] == 1) {
            paths += sums[i]; 
        }
    }


    product = one_jolt * three_jolts;
    //printf("1 jolt differences: %d\n3 jolt differences: %d\n", one_jolt, three_jolts);
    printf("(Part 1) Product of 1 & 3 jolt differences: %d\n", product);
    printf("(Part 2) Arrangements of adapters: %lld\n", paths);

    return 0;
}
