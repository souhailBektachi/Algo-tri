#include "caseLib.h"
#include "stdlib.h"

void generateRandomArray(int *tab, int size)
{
    for (int i = 0; i < size; i++)
    {
        tab[i] = rand() % size;
    }
}

void generateSortedArray(int *tab, int size)
{
    for (int i = 0; i < size; i++)
    {
        tab[i] = i;
    }
}

void generateReversedArray(int *tab, int size)
{
    for (int i = 0; i < size; i++)
    {
        tab[i] = size - i - 1;
    }
}

void generateArrayWithDuplicates(int *tab, int size)
{
    for (int i = 0; i < size; i++)
    {
        tab[i] = rand() % 10; // Adjust the number of unique values as needed
    }
}

void generateArrayWithSmallRange(int *tab, int size)
{
    for (int i = 0; i < size; i++)
    {
        tab[i] = rand() % 500;
    }
}

void generateArrayWithOutliers(int *tab, int size)
{
    for (int i = 0; i < size; i++)
    {
        tab[i] = (rand() % size) * 10000;
    }
    tab[size - 1] = tab[size - 1 - size / 2] = tab[size - 1 - size / 4] = tab[size - 1 - size / 8] = 0;
}

void generateArrayWithEqualElements(int *tab, int size)
{
    if (size == 0)
        return;

    int value = rand() % size;
    for (int i = 0; i < size; i++)
    {
        tab[i] = value;
    }
}