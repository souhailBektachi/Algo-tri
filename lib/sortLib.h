#ifndef SORTLIB_H
#define SORTLIB_H

void bubbleSort(int arr[], int size);
void selectionSort(int arr[], int size);
void insertionSort(int arr[], int size);
void mergeSort(int arr[], int left, int right);
void quickSort(int arr[], int low, int high);
void heapSort(int arr[], int size);
void countingSort(int arr[], int size);
void radixSort(int arr[], int size);
void shellSort(int arr[], int size);
void cocktailSort(int arr[], int size);

typedef struct SortAlgo
{
    char *name;
    char *nameFr;
    void (*sort)();
    int hasAdditionalParam;
} SortAlgo;

const static SortAlgo ALGO_LIST[] = {
    {"BubbleSort", "Tri à bulles", bubbleSort, 0},
    {"SelectionSort", "Tri par sélection", selectionSort, 0},
    {"CocktailSort", "Tri cocktail", cocktailSort, 0},
    {"InsertionSort", "Tri d'insertion", insertionSort, 0},
    {"RadixSort", "Tri par base", radixSort, 0},
    {"HeapSort", "Tri par tas", heapSort, 0},
    {"ShellSort", "Tri de Shell", shellSort, 0},
    {"MergeSort", "Tri fusion", mergeSort, 1},
    {"QuickSort", "Tri rapide", quickSort, 1},
};

#endif