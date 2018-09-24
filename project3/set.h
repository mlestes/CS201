#ifndef __SET_H__
#define __SET_H__

#include <stdio.h>

typedef struct set SET;

extern SET *newSET(void (*)(FILE *, void *));
extern int makeSET(SET *, void *);
extern int findSET(SET *, int);
extern int unionSET(SET *, int, int);
extern int countSET(SET *);
extern int displaySET(FILE *, SET *);

#endif
