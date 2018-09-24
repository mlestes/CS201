#ifndef __SORT_H__
#define __SORT_H__

#include <stdio.h>
#include "da.h"

extern void csort(DA *, int (*)(void *, void *)); //counting sort
extern void msort(DA *, int (*)(void *, void *)); //merge sort

#endif
