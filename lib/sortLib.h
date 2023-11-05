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
    {"Insertion Sort", "Tri d'insertion", insertionSort, 0},
    {"Bubble Sort", "Tri à bulles", bubbleSort, 0},
    {"Selection Sort", "Tri par sélection", selectionSort, 0},
    {"Merge Sort", "Tri fusion", mergeSort, 1},
    {"Quick Sort", "Tri rapide", quickSort, 1},
    {"Heap Sort", "Tri par tas", heapSort, 0},
    {"Radix Sort", "Tri par base", radixSort, 0},
    {"Shell Sort", "Tri de Shell", shellSort, 0},
    {"Cocktail Sort", "Tri cocktail", cocktailSort, 0},
};

#endif