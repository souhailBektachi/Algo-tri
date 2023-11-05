#include <stdio.h>
#include "lib/sortLib.h"
#include "lib/funcLib.h"
#include "lib/dataLib.h"

int main(int argc, char const *argv[])
{
    if (argc < 4)
    {
        printf("Usage: %s <initial_size> <step> <nb_step> <nb_cases> [smoothed]\n", argv[0]);
        return 1;
    }

    INIT_SIZE = atoi(argv[1]);
    STEP = atoi(argv[2]);
    NB_STEP = atoi(argv[3]);
    CASES = atoi(argv[4]) >=7 ? 7:atoi(argv[4]);
    SMOOTHED = argc >= 6 ? atoi(argv[5]) : 0;

    point M[sizeof(ALGO_LIST) / sizeof(SortAlgo)][NB_STEP];
    remplir_matrice_temp(M);
    // affiche_matrice(M);
    gnerateDataFiles(M);
    visualizeData();
}