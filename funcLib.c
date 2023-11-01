#include "funcLib.h"
#include "sortLib.h"
// #include <pthread.h>

void random_v(int *tab, int taille)
{
    int i;
    for (i = 0; i < taille; i++)
    {
        tab[i] = rand() % 100;
    }
}

// ----------------------------------------------------------------------------------------

// Fonction qui mesure le temps d'exécution d'une autre fonction
double mesureTemps(void (*fonction)(), int taille, int tab[])
{
    // int *tab;
    // tab=(int*)malloc(taille*sizeof(int));

    clock_t start, end;
    double cpu_time_used;

    // Enregistrez le moment où vous démarrez la mesure du temps
    start = clock();

    // Appelez la fonction dont vous souhaitez mesurer le temps
    fonction(tab, taille);
    // Enregistrez le moment où la fonction a terminé
    end = clock();
    // Calculez le temps d'exécution en secondes
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}
// ----------------------------------------------------------------------------------------
void remplir_matrice_temp(point M[8][10])
{
    int i,j,taille=1000,*tab;
    double t;
    tab=(point*)malloc(taille*sizeof(point));
    random_v(tab,taille);
    for(i=0;i<10;i++)
    {
            M[0][i].time=mesureTemps(bubbleSort,taille,tab);
            M[1][i].time=mesureTemps(selectionSort,taille,tab);
            M[2][i].time=mesureTemps(insertionSort,taille,tab);
            M[3][i].time=mesureTemps(heapSort,taille,tab);
            M[4][i].time=mesureTemps(countingSort,taille,tab);
            M[5][i].time=mesureTemps(radixSort,taille,tab);
            M[6][i].time=mesureTemps(shellSort,taille,tab);
            M[7][i].time=mesureTemps(cocktailSort,taille,tab);
            for(j=0;j<8;j++){
                M[j][i].size=taille;
            }
            free(tab);
            taille+=10000;
            tab=(int*)malloc(taille * sizeof(int));
            random_v(tab,taille);
    }
}
// ----------------------------------------------------------------------------------------
void affiche_matrice(point M[8][10])
{
    int i, j, taille = 1000;

    for (j = 0; j < 10; j++)
    {
        printf("|%-10d", M[0][j].size);
    }

    printf("|\n");

    for (j = 0; j < 10; j++)
    {
        printf("|----------");
    }

    printf("|");

    for (i = 0; i < 8; i++)
    {
        printf("\n");
        for (j = 0; j < 10; j++)
        {
            printf("|%-10lf", M[i][j].time);
        }
        printf("|");
    }
    printf("\n");
}