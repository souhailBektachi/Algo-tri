void generateSortedArray(int *tab, int n);
void generateBalancedPartitionsArray(int *tab, int n);
void generateLimitedRangeArray(int *tab, int n);
void generateSmallSubarraySizesArray(int *tab, int n);
void generateReverseSortedArray(int *tab, int n);
void generateUnbalancedPartitionsArray(int *tab, int n);
void generateLargeRangeArray(int *tab, int n);

typedef struct Case
{
    char *name;
    char *nameFr;
    char *label;
    void (*generate)(int *, int);
} Case;

const static Case CASES_LIST[] = {
    {"Sorted Array", "Tableau trié", "sorted", generateSortedArray},
    {"Balanced Partitions Array", "Tableau avec partitions équilibrées", "balanced", generateBalancedPartitionsArray},
    {"Limited Range Array", "Tableau avec plage limitée", "limited", generateLimitedRangeArray},
    {"Small Subarray Sizes Array", "Tableau avec petites tailles de sous-tableaux", "small", generateSmallSubarraySizesArray},
    {"Reverse Sorted Array", "Tableau trié à l'envers", "reverse", generateReverseSortedArray},
    {"Unbalanced Partitions Array", "Tableau avec partitions déséquilibrées", "unbalanced", generateUnbalancedPartitionsArray},
    {"Large Range Array", "Tableau avec grande plage", "large", generateLargeRangeArray},
};