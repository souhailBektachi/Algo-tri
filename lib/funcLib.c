#include "funcLib.h"
#include "sortLib.h"
#include <string.h>
#include <unistd.h>

int INIT_SIZE, STEP, NB_STEP;

void random_v(int *tab, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        tab[i] = rand();
    }
}

// ----------------------------------------------------------------------------------------

// Fonction qui mesure le temps d'exécution d'une autre fonction
double mesureTemps(void (*fonction)(), int size, int tab[])
{

    int *tabClone;
    tabClone = (int *)malloc(size * sizeof(int));

    memcpy(tabClone, tab, size * sizeof(int));

    double real_time_passed;
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    fonction(tabClone, size);
    clock_gettime(CLOCK_MONOTONIC, &end);

    real_time_passed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    free(tabClone);
    return real_time_passed;
}
// ----------------------------------------------------------------------------------------

void *threadFunc(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    *(data->recordTab) = (point){data->size, mesureTemps(data->sort, data->size, data->tab)};
    data->done = 1;
    printf("%s, ", data->name);
    return NULL;
}

void remplir_matrice_temp(point M[][NB_STEP])
{
    int i = 0, *tab, size = INIT_SIZE;
    pthread_t threads[sizeof(ALGO_LIST) / sizeof(sortAlgo)][NB_STEP];
    ThreadData threadData[sizeof(ALGO_LIST) / sizeof(sortAlgo)][NB_STEP];
    int *pointers[NB_STEP];

    do
    {
        tab = (int *)malloc(size * sizeof(int));
        pointers[i] = tab;

        random_v(tab, size);

        for (int j = 0; j < sizeof(ALGO_LIST) / sizeof(sortAlgo); j++)
        {
            threadData[j][i] = (ThreadData){&M[j][i], ALGO_LIST[j].sort, size, tab, ALGO_LIST[j].name};
            pthread_create(&threads[j][i], NULL, threadFunc, &threadData[j][i]);
        }

        size += STEP;
        i++;
    } while (i < NB_STEP);

    showLoading(threadData);

    for (int i = 0; i < sizeof(ALGO_LIST) / sizeof(sortAlgo); i++)
    {
        for (int j = 0; j < NB_STEP; j++)
        {
            pthread_join(threads[i][j], NULL);
        }
    }

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

    for (i = 0; i < sizeof(ALGO_LIST) / sizeof(sortAlgo); i++)
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

void showLoading(ThreadData data[][NB_STEP])
{
    int algoCount = sizeof(ALGO_LIST) / sizeof(sortAlgo);
    int allDone = 0;
    int counter = 0;

    while (!allDone)
    {
        printf("\033[H\033[J");
        printf("counter: %d\n", counter++);

        allDone = 1;

        for (int i = 0; i < algoCount; i++)
        {
            int algoDone = 1;

            for (int j = 0; j < NB_STEP; j++)
            {
                if (!data[i][j].done)
                {
                    algoDone = 0;
                    allDone = 0;
                }
            }

            printf("%-40s %s\n", data[i][0].name, algoDone ? "Done" : "Waiting...");
        }

        sleep(1);
    }

    printf("\033[H\033[J");
}