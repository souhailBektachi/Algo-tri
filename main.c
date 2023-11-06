#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/sortLib.h"
#include "lib/funcLib.h"
#include "lib/dataLib.h"
#include "lib/caseLib.h"

int main(int argc, char const *argv[])
{
    if (argc < 4)
    {
        printf("Usage: %s <initial_size> <step> <nb_step> [case]\n", argv[0]);
        return 1;
    }

    INIT_SIZE = atoi(argv[1]);
    STEP = atoi(argv[2]);
    NB_STEP = atoi(argv[3]);
    SMOOTHED = 1;

    srand(time(NULL));

    if (argc >= 5)
    {
        SHOW = 1;
        CASES = atoi(argv[4]) >= NB_CASES ? NB_CASES - 1 : atoi(argv[4]);
        point M[sizeof(ALGO_LIST) / sizeof(SortAlgo)][NB_STEP];
        remplir_matrice_temp(M);
        gnerateDataFiles(M);
        visualizeData();
    }
    else
    {
        for (int i = 0; i < NB_CASES; i++)
        {
            CASES = i;
            point M[sizeof(ALGO_LIST) / sizeof(SortAlgo)][NB_STEP];
            remplir_matrice_temp(M);
            gnerateDataFiles(M);
            visualizeData();
        }
    }
}