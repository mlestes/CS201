#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "str.h"

/*****************************************************************************/
/* str.c BY Murray Estes                                                     */
/* PURPOSE: To implement a string class for wrapping strings into a generic  */
/*          data structure.                                                  */
/* METHOD DESCRIPTION:                                                       */
/*     string *newString(char *val);                                         */
/*         Creates a new String object with the given c string.              */
/*                                                                           */
/*     char *getString(string *str);                                         */
/*         Returns the c-string stored in the object.                        */
/*                                                                           */
/*     char *setString(string *str, char *val);                              */
/*         Sets the new c-string into the object. Returns the old c-string.  */
/*                                                                           */
/*     void printString(FILE *fp, void *str);                              */
/*         Displays the c-string in the object.                              */
/*                                                                           */
/*****************************************************************************/

/*** STUCTURE DEFINITION ***/
struct STRING{

    char *value;

    };

/*** PRIVATE FUNCTIONS ***/
//none

/*** PUBLIC METHODS ***/
string *newString(char *val){

    string *str = malloc(sizeof(string));
    assert(str != 0);
    str->value = val;

    return str;

    }

char *getString(string *str){

    return str->value;

    }

char *setString(string *str, char *val){

    char *thing = str->value;
    str->value = val;

    return thing;

    }

void printString(FILE *fp, void *str){

    string *s = (string *) str;
    fprintf(fp, "%s", s->value);

    }

int sizeString(string *str){

    return strlen(str->value);

    }

int compareString(void *a, void *b){

    string *alpha = (string *) a;
    string *beta = (string *) b;
    return strcmp(alpha->value, beta->value);

    }

/*** PRIVATE FUNCTIONS ***/
//none
