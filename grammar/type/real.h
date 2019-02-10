#ifndef __REAL_H__
#define __REAL_H__

#include <stdio.h>

typedef struct REAL real;

real *newReal(double);
double getReal(real *);
double setReal(real *, double);
void printReal(FILE *, void *);
int compareReal(void *, void *);

#endif
