#include <stdio.h>
#include "lib/sortLib.h"
#include "lib/funcLib.h"

int main(int argc, char const *argv[])
{
    if (argc < 4)
    {
        printf("Usage: %s <initial_size> <step> <nb_step> [smoothed]\n", argv[0]);
        return 1;
    }

    INIT_SIZE = atoi(argv[1]);
    STEP = atoi(argv[2]);
    NB_STEP = atoi(argv[3]);
    SMOOTHED = argc >= 5 ? atoi(argv[4]) : 0;

    point M[sizeof(ALGO_LIST) / sizeof(sortAlgo)][NB_STEP];
    remplir_matrice_temp(M);
    // affiche_matrice(M);
    gnerateDataFiles(M);
    visualizeData();
}