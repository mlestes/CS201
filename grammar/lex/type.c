/*****************************************************************************/
// type.c by Murray Estes
// A custom type class used to store multiple types in one class
// Date Began: 20190117
// Date Completed:
/*****************************************************************************/
// Usage:
// type *newType(void *) - creates a new type object.
// 	type *t = newType(32);
//
// void *getTypeValue(type *) - returns the stored type object's value.
// 	int *x = (int *) getTypeValue(t);
//
// char *getTypeCast(type *) - returns the type of the stored object.
// 	char *objType = getTypeCast(t);
//
/*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "type.h"

/*** STRUCTRES ***/
struct Type{
    
    char *cast;
    int ival;
    double rval;
    char *sval;

};

/*** PRIVATE FUNCTION DECLARATIONS ***/
int parseToken(void *);

/*** PUBLIC/MAIN FUNCTION DEFINITIONS ***/
type *newType(void *item){

    int parsed = parseToken(item);
    type *t = malloc(sizeof(type));
    switch (parsed){
        case 0:
            t->cast = INTEGER;
	    int *i = (int *) item;
	    t->ival = *i;
	    break;
	case 1:
	    t->cast = REAL;
	    doulbe *r = (double *) item;
	    t->rval = *r;
	    break;
	case 2:
	    t->cast = STRING;
	    t->sval = (char *) item;
	    break;
    }

    return t;

}

void *getTypeValue(type *t){

    switch (t->cast){
        case INTEGER:
            int *i = t->ival;
	    return i;
	    break;
	case REAL:
	    double *r = t->rval;
	    return r;
	    break;
	case STRING:
	    return t->sval;
	    break;	
    }

}

char *getTypeCast(type *t){return t->cast;}

/*** PRIVATE FUNCTION DEFINITIONS ***/
//parse token by char to determine type
int parseToken(void *item){

    char *token = (char *) item;
    int isint = 1;
    int isreal = 1;
    int isstring = 1;
    int dot = 0;
    int size = strlen(token);
    int i;
    for(i = 0; i < size; i++){
        if(isalpha(token[i])){
	    isreal = 0;
	    isint = 0;
	    break;
	}
	else if(!isdigit(token[i])){
            if(token[i] != '.' || (token[0] != '-' && !issdigit(token[0]))){
		isreal = 0;
		isint = 0;
		break;
	    }
	    else dot = 1;
	}
    }
    if(isint) isstring = 0;
    else if(dot) isint = 0;
    else isreal = 0;

    if(isint) return 0;
    else if(isreal) return 1;
    else return 2;

}

