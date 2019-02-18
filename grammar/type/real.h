#ifndef __REAL_H__
#define __REAL_H__

#include <stdio.h>

typedef struct Real_Type real_t;

real_t *newReal(double value);
double getReal(real_t *r);
double setReal(real_t *r, double value);
void printReal(FILE *fp, void *r);
int compareReal(void *a, void *b);

#endif
