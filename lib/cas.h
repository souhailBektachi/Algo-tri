void generateSortedArray(int* tab, int n);
void generateBalancedPartitionsArray(int* tab, int n);
void generateLimitedRangeArray(int* tab, int n);
void generateSmallSubarraySizesArray(int* tab, int n);
void generateReverseSortedArray(int* tab, int n);
void generateUnbalancedPartitionsArray(int* tab, int n);
void generateLargeRangeArray(int* tab, int n);
const static void (*CASES_LIST[])() = {
    generateSortedArray,
    generateBalancedPartitionsArray,
    generateLimitedRangeArray,
    generateSmallSubarraySizesArray,
    generateReverseSortedArray,
    generateUnbalancedPartitionsArray,
    generateLargeRangeArray
};

