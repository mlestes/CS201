#include <stdio.h>
#include <stdlib.h>
#include "real.h"

/*****************************************************************************/
/* real.c BY Murray Estes.                                                   */
/* PURPOSE: To implement a wrapper for real (type double) items for use in   */
/*          generic data structures.                                         */
/* METHOD DESCRIPTIONS:                                                      */
/*     real *newReal(double value);                                          */
/*         Creates a new real object.                                        */
/*                                                                           */
/*     double getReal(real *r);                                              */
/*         Returns the stored value.                                         */
/*                                                                           */
/*     double setReal(real *r, double *value);                               */
/*         Replaces the stored value with the given one. Returns the old     */
/*         value.                                                            */
/*                                                                           */
/*     void printReal(FILE *fp, real *r);                                    */
/*         Prints the stored value to the supplied output stream.            */
/*                                                                           */
/*     int compareReal(void *a, void *b);                                    */
/*         Returns negative if a is lesser. Returns positive if b is lesser. */
/*         Returns 0 = a == b.                                               */
/*                                                                           */
/*****************************************************************************/

struct REAL{

    double value;

    };

/*** PRIVATE FUNCTION SIGNATURES ***/
//none

/*** PUBLIC METHODS ***/
real *newReal(double value){

    real *r = malloc(sizeof(real));
    if(r == 0){
        fprintf(stderr, "Failed to allocate memory!\n");
        exit(1);
        }
    r->value = value;

    return r;

    }

double getReal(real *r){return r->value;}
double setReal(real *r, double value){

    double old = r->value;
    r->value = value;

    return old;

    }

void printReal(FILE *fp, void *r){

    real *d = (real *) r;
    fprintf(fp, "%f", d->value);

    }

int compareReal(void *a, void *b){

    real *alpha = (real *) a;
    real *beta = (real *) b;
    return alpha->value - beta->value;

    }

/*** PRIVATE FUNCTIONS ***/
//none
