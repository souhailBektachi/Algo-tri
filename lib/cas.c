#include "cas.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
void generateSortedArray(int* tab, int n) {
    for (int i = 0; i < n; ++i) {
        tab[i] = i;
    }
}

void fisherYatesShuffle(int* arr, int size) {
    srand(time(NULL));
    for (int i = size - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
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

    fisherYatesShuffle(tab, n);
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
    for (int i = 0; i < n; ++i) {
        tab[i] = i + 1;
    }
    fisherYatesShuffle(tab, n);
}

void generateLargeRangeArray(int* tab, int n) {
    srand(time(NULL)); 
    int range = n * 10; 
    for (int i = 0; i < n; ++i) {
        tab[i] = rand() % range;
    }
}

