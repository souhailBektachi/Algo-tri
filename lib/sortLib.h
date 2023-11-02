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

typedef struct sortAlgo
{
    char *name;
    char *color;
    void (*sort)();
} sortAlgo;

const static sortAlgo ALGO_LIST[] = {
    {"insertionSort", "green", insertionSort},
    {"bubbleSort", "red", bubbleSort},
    {"selectionSort", "blue", selectionSort},
    {"heapSort", "purple", heapSort},
    {"radixSort", "pink", radixSort},
    {"shellSort", "gray", shellSort},
    {"cocktailSort", "black", cocktailSort},
};