#ifndef __INT_H__
#define __INT_H__

#include <stdio.h>

typedef struct Integer_Type integer_t;

integer_t *newInteger(int value);
int getInteger(integer_t *i);
int setInteger(integer_t *i, int value);
void printInteger(FILE *fp, void *i);
int compareInteger(void *a, void *b);

#endif
