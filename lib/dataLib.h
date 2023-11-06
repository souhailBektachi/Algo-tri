#include "funcLib.h"

#ifndef DATA_LIB_H
#define DATA_LIB_H

extern int SMOOTHED, SHOW;

void gnerateDataFiles(point M[][NB_STEP]);
void visualizeData();
void smoothData(point M[][NB_STEP]);
double smooth(double xMinus2, double xMinus1, double x, double xPlus1, double xPlus2);

#endif