#include "cas.h"
#include <stdlib.h>
#include <time.h>

void generateSortedArray(int* tab, int n) {
    for (int i = 0; i < n; ++i) {
        tab[i] = i;
    }
}

void generateBalancedPartitionsArray(int* tab, int n) {
    int value = 1;
    for (int i = 0; i < n; ++i) {
        tab[i] = value;
        value += 2;
        if (value > n * 2) {
            value = 2;
        }
    }
}

void generateLimitedRangeArray(int* tab, int n) {
    srand(time(NULL)); 
    int range = n * 2; 
    for (int i = 0; i < n; ++i) {
        tab[i] = rand() % range;
    }
}

void generateSmallSubarraySizesArray(int* tab, int n) {
    int subarraySize = 1;
    for (int i = 0; i < n; ++i) {
        tab[i] = subarraySize;
        subarraySize = (subarraySize % 5) + 1;
    }
}

void generateReverseSortedArray(int* tab, int n) {
    for (int i = 0; i < n; ++i) {
        tab[i] = n - i - 1;
    }
}

void generateUnbalancedPartitionsArray(int* tab, int n) {
    int value = 1;
    for (int i = 0; i < n; ++i) {
        tab[i] = value;
        value += (i % 2) + 1;
    }
}

void generateLargeRangeArray(int* tab, int n) {
    srand(time(NULL)); 
    int range = n * 10; 
    for (int i = 0; i < n; ++i) {
        tab[i] = rand() % range;
    }
}
