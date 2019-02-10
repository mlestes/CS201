#ifndef __REAL_H__
#define __REAL_H__

#include <stdio.h>

typedef struct Real_Type real_t;

real_t *newReal(double);
double getReal(real_t *);
double setReal(real_t *, double);
void printReal(FILE *, void *);
int compareReal(void *, void *);

#endif
