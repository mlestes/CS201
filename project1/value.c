#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "value.h"

/*****************************************************************************/
/* value.c BY Murray Estes                                                   */
/* PURPOSE: To implement a value object that can distinguish between multiple*/
/*          types.                                                           */
/* METHOD DESCRIPTIONS:                                                      */
/*     value *newValue(void *val, int type, void (*d)(FILE*, void *));       */
/*         Creates a new object. Parameters are the value, a flag for the    */
/*         type, and a display function.                                     */
/*                                                                           */
/*     void *getValue(value *val);                                           */
/*         Returns the stored value.                                         */
/*                                                                           */
/*     int getValueType(value *val);                                         */
/*         Returns the flag for the value type.                              */
/*                                                                           */
/*     void displayValue(FILE *fp, value *val);                              */
/*         Displays the stored value using the provided display function.    */
/*                                                                           */
/*****************************************************************************/

#define INTEGER 1
#define REAL 2
#define STRING 3

struct VALUE{

    void *store;
    int type;
    void (*display)(FILE *, void *);

    };

/*** PRIVATE FUNCTION SIGNATURES ***/
//none

/*** PUBLIC METHODS ***/
value *newValue(void *val, int type, void (*d)(FILE *, void *)){

    value *v = malloc(sizeof(value));
    v->store = val;
    v->type = type;
    v->display = d;

    return v;

    }

void *getValue(value *val){

    return val->store;

    }

int getValueType(value *val){

    return val->type;

    }

void displayValue(FILE *fp, value *val){

    val->display(fp, val->store);

    }

/*** PRIVATE FUNCTIONS ***/
//none
