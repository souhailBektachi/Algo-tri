#include "dataLib.h"
#include "funcLib.h"
#include "sortLib.h"

int SMOOTHED;

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