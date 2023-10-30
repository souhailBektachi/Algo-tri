#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct point
{
    int size;
    double time;
} point;

void random_v(int *tab, int taille);
double mesureTemps(void (*fonction)(), int taille, int *tab);
void remplir_matrice_temp(point M[2][10]);
void affiche_matrice(point M[2][10]);