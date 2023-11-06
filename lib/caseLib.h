#ifndef CASELIB_H
#define CASELIB_H
void generateRandomArray(int *tab, int size);             // 0
void generateSortedArray(int *tab, int size);             // 1
void generateReversedArray(int *tab, int size);           // 2
void generateArrayWithDuplicates(int *tab, int size);     // 3
void generateArrayWithSmallRange(int *tab, int size);     // 4
void generateArrayWithOutliers(int arr[], int size);      // 5
void generateArrayWithEqualElements(int arr[], int size); // 6

typedef struct Case
{
    char *name;
    char *nameFr;
    char *label;
    void (*generate)(int *, int);
} Case;

const static Case CASES_LIST[] = {
    {"Random Array", "Tableau aléatoire", "random", generateRandomArray},
    {"Sorted Array", "Tableau trié", "sorted", generateSortedArray},
    {"Reversed Array", "Tableau trié inversé", "reversed", generateReversedArray},
    {"Array with duplicates", "Tableau avec doublons", "duplicates", generateArrayWithDuplicates},
    {"Array with small range", "Tableau avec petite plage", "small_range", generateArrayWithSmallRange},
    {"Array with outliers", "Tableau avec valeurs aberrantes", "outliers", generateArrayWithOutliers},
    {"Array with equal elements", "Tableau avec valeurs égales", "equal_elements", generateArrayWithEqualElements},
};

const static int NB_CASES = sizeof(CASES_LIST) / sizeof(Case);

#endif