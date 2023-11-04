#include "funcLib.h"
#include "sortLib.h"
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int INIT_SIZE, STEP, NB_STEP, SMOOTHED;

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
    return NULL;
}

void remplir_matrice_temp(point M[][NB_STEP])
{
    int i = 0, *tab, size = INIT_SIZE;
    pthread_t threads[sizeof(ALGO_LIST) / sizeof(sortAlgo)];
    ThreadData threadData[sizeof(ALGO_LIST) / sizeof(sortAlgo)];
    int *pointers[NB_STEP];

    do
    {
        tab = (int *)malloc(size * sizeof(int));

        pointers[i] = tab;

        random_v(tab, size);

        for (int j = 0; j < sizeof(ALGO_LIST) / sizeof(sortAlgo); j++)
        {
            threadData[j] = (ThreadData){&M[j][i], ALGO_LIST[j].sort, size, tab, ALGO_LIST[j].name};
            pthread_create(&threads[j], NULL, threadFunc, &threadData[j]);
        }

        showLoading(threadData, i + 1);

        // for (int i = 0; i < sizeof(ALGO_LIST) / sizeof(sortAlgo); i++)
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

void showLoading(ThreadData data[], int cycle)
{
    int algoCount = sizeof(ALGO_LIST) / sizeof(sortAlgo);
    int allDone;
    int done[algoCount];
    float counter = 0;

    do
    {
        allDone = 1;
        printf("\033[H\033[J");
        printf("Cycle %d/%d %30.2f\n\n\n", cycle, NB_STEP, counter);

        for (int i = 0; i < algoCount; i++)
        {
            printf("%-40s %s\n", data[i].name, data[i].done ? "Done" : "Loading...");
            allDone = allDone & data[i].done;
        }

        usleep(10000);
        counter += 0.01;
    } while (!allDone);

    printf("\033[H\033[J");
}

void gnerateDataFiles(point M[][NB_STEP])
{
    FILE *fp, *sfp;
    char fileName[50], sFileName[50];
    int i, j;

    CREATE_DIR("data");
    CREATE_DIR("data/smoothed");

    for (i = 0; i < sizeof(ALGO_LIST) / sizeof(sortAlgo); i++)
    {

        sprintf(fileName, "data/%s.dat", ALGO_LIST[i].name);
        fp = fopen(fileName, "w");

        if (SMOOTHED)
        {
            sprintf(sFileName, "data/smoothed/%s.dat", ALGO_LIST[i].name);
            sfp = fopen(sFileName, "w");
        }

        if (fp == NULL || (SMOOTHED && sfp == NULL))
        {
            printf("Error opening file!\n");
            exit(1);
        }

        for (j = 0; j < NB_STEP; j++)
        {
            fprintf(fp, "%d %lf\n", M[i][j].size, M[i][j].time);
            if (SMOOTHED && j > 1 && j < NB_STEP - 2)
            {
                fprintf(sfp, "%d %lf\n", M[i][j].size, smooth(M[i][j - 2].time, M[i][j - 1].time, M[i][j].time, M[i][j + 1].time, M[i][j + 2].time));
            }
            else
            {
                fprintf(sfp, "%d %lf\n", M[i][j].size, M[i][j].time);
            }
        }

        fclose(fp);
        (SMOOTHED) ? fclose(sfp) : (void)(0);
    }
}

void visualizeData()
{
    int algoCount = sizeof(ALGO_LIST) / sizeof(sortAlgo);
    FILE *script, *scriptSm;

    script = fopen("script.txt", "w");
    scriptSm = fopen("script_smoothed.txt", "w");

    fprintf(script, "set title 'Comparaison des algorithmes de tri'\n");
    fprintf(script, "set xlabel 'Taille du tableau'\n");
    fprintf(script, "set ylabel 'Temps d''execution'\n");
    fprintf(script, "set key left top\n");
    fprintf(script, "set grid\n");
    fprintf(script, "plot ");

    if (SMOOTHED)
    {
        fprintf(scriptSm, "set title 'Comparaison des algorithmes de tri (lissé)'\n");
        fprintf(scriptSm, "set xlabel 'Taille du tableau'\n");
        fprintf(scriptSm, "set ylabel 'Temps d''execution'\n");
        fprintf(scriptSm, "set key left top\n");
        fprintf(scriptSm, "set grid\n");
        fprintf(scriptSm, "plot ");
    }

    for (int i = 0; i < algoCount; i++)
    {
        fprintf(script, "'data/%s.dat' with lines title '%s'", ALGO_LIST[i].name, ALGO_LIST[i].name);
        (SMOOTHED) ? fprintf(scriptSm, "'data/smoothed/%s.dat' with lines title '%s'", ALGO_LIST[i].name, ALGO_LIST[i].name) : (void)(0);
        if (i < algoCount - 1)
        {
            fprintf(script, ",\\\n");
            (SMOOTHED) ? fprintf(scriptSm, ",\\\n") : (void)(0);
        }
    }

    fclose(script);
    (SMOOTHED) ? fclose(scriptSm) : (void)(0);
    system("gnuplot -p 'script.txt'");
    system("gnuplot -p 'script_smoothed.txt'");
}

double smooth(double xMinus2, double xMinus1, double x, double xPlus1, double xPlus2)
{
    return (xMinus2 + xMinus1 + x + xPlus1 + xPlus2) / 5;
}