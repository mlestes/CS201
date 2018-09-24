#include <stdio.h>
#include <stdlib.h>
#include "int.h"

/*****************************************************************************/
/* int.c BY Murray Estes.                                                    */
/* PURPOSE: To implment a wrapper for integers to be used in generic data    */
/*          structures.                                                      */
/* METHOD DESCRIPTIONS:                                                      */
/*     integer *newInteger(int value);                                       */
/*         Creates a new integer object.                                     */
/*                                                                           */
/*     int getInteger(integer *i);                                           */
/*         Returns the stored int value.                                     */
/*                                                                           */
/*     int setInteger(integer *i, int value);                                */
/*         Replaces the stored value with the given one. Returns the old     */
/*         one.                                                              */
/*                                                                           */
/*     void printInteger(FILE *fp, integer *i);                              */
/*         Prints out the stored value to the supplied stream.               */
/*                                                                           */
/*     int compareInteger(integer *a, integer *b);                           */
/*         Returns negative if the first in less. Returns positve if the     */
/*         second is lesser. Returns 0 if they are equal.                    */
/*                                                                           */
/*****************************************************************************/

struct INTEGER{

    int value;

    };

/*** PRIVATE FUNCTION SIGNATURES ***/
//none

/*** PUBLIC METHODS ***/
integer *newInteger(int value){

    integer *i = malloc(sizeof(integer));
    if(i == 0){
        fprintf(stderr, "Failure to allocate memory.\n");
        exit(1);
        }
    i->value = value;

    return i;

    }

int getInteger(integer *i){

    return i->value;

    }

int setInteger(integer *i, int value){

    int old = i->value;
    i->value = value;

    return old;

    }

void printInteger(FILE *fp, void *i){

    integer *x = (integer *)i;
    fprintf(fp, "%d", x->value);

    }

int compareInteger(void *a, void *b){

    integer *alpha = (integer *)a;
    integer *beta = (integer *)b;
    return alpha->value - beta->value;

    }

/*** PRIVATE FUNCTIONS ***/
//none
