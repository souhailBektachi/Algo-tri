#include "funcLib.h"
#include "sortLib.h"
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int INIT_SIZE, STEP, NB_STEP;

void random_v(int *tab, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        tab[i] = rand() % 100;
    }
}

// ----------------------------------------------------------------------------------------

// Fonction qui mesure le temps d'exécution d'une autre fonction
double mesureTemps(void (*fonction)(), int size, int tab[])
{

    int *tabClone;
    tabClone = (int *)malloc(size * sizeof(int));

    memccpy(tabClone, tab, size, sizeof(int));

    clock_t start, end;
    double cpu_time_used;

    // Enregistrez le moment où vous démarrez la mesure du temps
    start = clock();

    // Appelez la fonction dont vous souhaitez mesurer le temps
    fonction(tabClone, size);
    // Enregistrez le moment où la fonction a terminé
    end = clock();
    // Calculez le temps d'exécution en secondes
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    free(tabClone);
    return cpu_time_used;
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