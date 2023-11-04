#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

extern int INIT_SIZE, STEP, NB_STEP;

typedef struct point
{
    int size;
    double time;
} point;

typedef struct
{
    point *recordTab;
    void (*sort)();
    int size;
    int *tab;
    char *name;
    int done;
} ThreadData;

void random_v(int *tab, int taille);
double mesureTemps(void (*fonction)(), int size, int *tab);
void remplir_matrice_temp(point M[][NB_STEP]);
void affiche_matrice(point M[][NB_STEP]);
void showLoading(ThreadData data[], int cycle);
void gnerateDataFiles(point M[][NB_STEP]);
void visualizeData();

#ifdef _WIN32
#include <direct.h>
#define CREATE_DIR(dir) _mkdir(dir)
#else
#include <sys/stat.h>
#define CREATE_DIR(dir) mkdir(dir, 0777)
#endif