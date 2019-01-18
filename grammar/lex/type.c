/*****************************************************************************/
// type.c by Murray Estes
// A custom type class used to store multiple types in one class
// Date Began: 20190117
// Date Completed:
/*****************************************************************************/
// Usage:
// type_t *newType(void *) - creates a new type object.
// 	type_t *t = newType(32);
//
// void *getTypeValue(type_t *) - returns the stored type object's value.
// 	int *x = (int *) getTypeValue(t);
//
// char *getTypeCast(type_t *) - returns the type of the stored object.
// 	char *objType = getTypeCast(t);
//
/*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "type.h"
#include "int.h"
#include "real.h"
#include "str.h"

#define INT 0
#define DBL 1
#define STR 2

/*** STRUCTRES ***/
struct Type_type{
    
    char *cast;
    integer *ival;
    real *rval;
    string *sval;

};

/*** PRIVATE FUNCTION DECLARATIONS ***/
int parseToken(void *);

/*** PUBLIC/MAIN FUNCTION DEFINITIONS ***/
type_t *newType(void *item){

    int parsed = parseToken(item);
    type_t *t = malloc(sizeof(type_t));
    switch (parsed){
        case INT:
            t->cast = INTEGER;
	    char *str = (char *) item;
	    int i = atoi(str);
	    t->ival = newInteger(i);
	    break;
	case DBL:
	    t->cast = REAL;
	    char *str = (char *) item;
	    double r = atof(str);
	    t->rval = newReal(r);
	    break;
	case STR:
	    t->cast = STRING;
	    char *str = (char *) item;
	    t->sval = newString(str);
	    break;
    }

    return t;

}

void *getTypeValue(type_t *t){

    switch (t->cast){
        case INTEGER:   
	    return t->ival;
	    break;
	case REAL:
	    return t->rval;
	    break;
	case STRING:
	    return t->sval;
	    break;	
    }

}

char *getTypeCast(type_t *t){return t->cast;}

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
            if(token[i] != '.' && dot == 0){ 
		isreal = 0;
		isint = 0;
		break;
	    }
	    else if(i == 0 && token[i] != '-'){
                isreal = 0;
	        isint = 0;
		break;
            }
            else if(token[i] == '.') dot = 1;
	}
    }
    if(isint) isstring = 0;
    else if(dot) isint = 0;
    else isreal = 0;

    if(isint) return INT;
    else if(isreal) return DBL;
    else return STR;

}

