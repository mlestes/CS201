#ifndef __INT_H__
#define __INT_H__

#include <stdio.h>

typedef struct INTEGER integer;

integer *newInteger(int);
int getInteger(integer *);
int setInteger(integer *, int);
void printInteger(FILE *, void *);
int compareInteger(void *, void *);

#endif
