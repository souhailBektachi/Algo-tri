#include "funcLib.h"
#include "sortLib.h"
#include <string.h>
#include <unistd.h>
#include "caseLib.h"
#include <pthread.h>

int INIT_SIZE, STEP, NB_STEP, CASES;

// void random_v(int *tab, int size)
// {
//     int i;
//     for (i = 0; i < size; i++)
//     {
//         tab[i] = rand();
//     }
// }

// ----------------------------------------------------------------------------------------

// Fonction qui mesure le temps d'exécution d'une autre fonction
double mesureTemps(SortAlgo algo, int size, int tab[])
{

    int *tabClone;
    tabClone = (int *)malloc(size * sizeof(int));

    memcpy(tabClone, tab, size * sizeof(int));

    double real_time_passed;
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    if (algo.hasAdditionalParam)
        algo.sort(tabClone, 0, size - 1);
    else
        algo.sort(tabClone, size);
    clock_gettime(CLOCK_MONOTONIC, &end);

    real_time_passed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    free(tabClone);
    return real_time_passed;
}
// ----------------------------------------------------------------------------------------

void *threadFunc(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    *(data->recordTab) = (point){data->size, mesureTemps(data->algo, data->size, data->tab)};
    data->done = 1;
    return NULL;
}

void remplir_matrice_temp(point M[][NB_STEP])
{
    int i = 0, *tab, size = INIT_SIZE;
    pthread_t threads[sizeof(ALGO_LIST) / sizeof(SortAlgo)];
    ThreadData threadData[sizeof(ALGO_LIST) / sizeof(SortAlgo)];
    int *pointers[NB_STEP];

    do
    {
        tab = (int *)malloc(size * sizeof(int));

        pointers[i] = tab;

        CASES_LIST[CASES].generate(tab, size);

        for (int j = 0; j < sizeof(ALGO_LIST) / sizeof(SortAlgo); j++)
        {
            threadData[j] = (ThreadData){&M[j][i], ALGO_LIST[j], size, tab};
            pthread_create(&threads[j], NULL, threadFunc, &threadData[j]);
        }

        showLoading(threadData, i + 1);

        // for (int i = 0; i < sizeof(ALGO_LIST) / sizeof(SortAlgo); i++)
        // {
        //     pthread_join(threads[i], NULL);
        // }

        size += STEP;
        i++;
    } while (i < NB_STEP);

    for (int i = 0; i < NB_STEP; i++)
    {
        free(pointers[i]);
    }
    printf("\n");
}
// ----------------------------------------------------------------------------------------
void affiche_matrice(point M[][NB_STEP])
{
    int i, j;

    printf("|%-20s", "");
    for (j = 0; j < NB_STEP; j++)
    {
        printf("|%-10d", M[0][j].size);
    }

    printf("|\n");

    printf("|--------------------");
    for (j = 0; j < NB_STEP; j++)
    {
        printf("|----------");
    }

    printf("|");

    for (i = 0; i < sizeof(ALGO_LIST) / sizeof(SortAlgo); i++)
    {
        printf("\n");
        printf("|%-20s", ALGO_LIST[i].name);

        for (j = 0; j < NB_STEP; j++)
        {
            printf("|%-10lf", M[i][j].time);
        }
        printf("|");
    }
    printf("\n");
}

void showLoading(ThreadData data[], int cycle)
{
    int algoCount = sizeof(ALGO_LIST) / sizeof(SortAlgo);
    int allDone;
    int done[algoCount];
    float counter = 0;

    do
    {
        allDone = 1;
        printf("\033[H\033[J");
        printf("Case: %s(%d/%d) %10s %d/%d %10.2fs\n\n\n", CASES_LIST[CASES].name, CASES + 1, NB_CASES, "Cycle", cycle, NB_STEP, counter);

        for (int i = 0; i < algoCount; i++)
        {
            printf("%-40s %s\n", data[i].algo.name, data[i].done ? "Done" : "Loading...");
            allDone = allDone & data[i].done;
        }

        usleep(10000);
        counter += 0.01;
    } while (!allDone);

    printf("\033[H\033[J");
}
