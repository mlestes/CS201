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
#include <ctype.h>
#include "type.h"
#include "int.h"
#include "real.h"
#include "str.h"
#include "arr.h"

/*** STRUCTRES ***/
struct Type_type{
    
    int cast;
    integer_t *ival;
    real_t *rval;
    string_t *sval;
	array_t *aval;

};

/*** PRIVATE FUNCTION DECLARATIONS ***/
//none

/*** PUBLIC/MAIN FUNCTION DEFINITIONS ***/
type_t *newType(void *item, int type){

    char *str;
    type_t *t = malloc(sizeof(type_t));
    switch (type){
        case INT:
            t->cast = INT;
			str = (char *) item;
	    	int i = atoi(str);
	    	t->ival = newInteger(i);
	    	break;
		case DBL:
	    	t->cast = DBL;
			str = (char *) item;
	    	double r = atof(str);
	    	t->rval = newReal(r);
	    	break;
		case STR:
		    t->cast = STR;
			str = (char *) item;
		    t->sval = newString(str);
	    	break;
		case ARR:
			t->cast = ARR;
			t->aval = new_array(printType);
			break;

    }

    return t;

}

void *getTypeValue(type_t *t){

    switch (t->cast){
        case INT: return t->ival;
		case DBL: return t->rval;
		case STR: return t->sval;
		case ARR: return t->aval;
    	default:  return "Error";

    }

}

int getTypeCast(type_t *t){return t->cast;}
void printType(FILE *fp, void *item){

	type_t *t = (type_t *) item;
	switch (t->cast)
	{
		case INT:
			printInteger(fp, t->ival);
			break;
		
		case DBL:
			printReal(fp, t->rval);
			break;
		
		case STR:
			printString(fp, t->sval);
			break;
		
		case ARR:
			print_array(fp, t->aval);
			break;
	
		default:
			break;
	}

}
/*** PRIVATE FUNCTION DEFINITIONS ***/
//none