#include "funcLib.h"
#include "sortLib.h"
#include <string.h>

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
    // int *tab;
    // tab=(int*)malloc(size*sizeof(int));

    int *tabClone;
    tabClone = (int *)malloc(size * sizeof(int));

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
void remplir_matrice_temp(point M[][NB_STEP])
{
    int i = 0, *tab, size = INIT_SIZE;
    do
    {
        tab = (int *)malloc(size * sizeof(int));
        if (tab == NULL)
        {
            printf("Erreur d'allocation de mémoire\n");
            exit(1);
        }

        random_v(tab, size);

        for (int j = 0; j < sizeof(ALGO_LIST) / sizeof(sortAlgo); j++)
        {
            M[j][i] = (point){size, mesureTemps(ALGO_LIST[j].sort, size, tab)};
        }

        size += STEP;
        free(tab);
        i++;
    } while (i < NB_STEP);
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