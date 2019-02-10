#ifndef __INT_H__
#define __INT_H__

#include <stdio.h>

typedef struct Integer_Type integer_t;

integer_t *newInteger(int);
int getInteger(integer_t *);
int setInteger(integer_t *, int);
void printInteger(FILE *, void *);
int compareInteger(void *, void *);

#endif
