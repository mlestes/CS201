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

/*** STRUCTRES ***/
struct Type_type{
    
    int cast;
    integer_t *ival;
    real_t *rval;
    string_t *sval;

};

/*** PRIVATE FUNCTION DECLARATIONS ***/
int parseToken(void *);

/*** PUBLIC/MAIN FUNCTION DEFINITIONS ***/
type_t *newType(void *item){

    char *str = (char *) item;
    int parsed = parseToken(item);
    type_t *t = malloc(sizeof(type_t));
    switch (parsed){
        case INT:
            t->cast = INT;
	    	int i = atoi(str);
	    	t->ival = newInteger(i);
	    	break;
		case DBL:
	    	t->cast = DBL;
	    	double r = atof(str);
	    	t->rval = newReal(r);
	    	break;
		case STR:
		    t->cast = STR;
		    t->sval = newString(str);
	    	break;
    }

    return t;

}

void *getTypeValue(type_t *t){

    switch (t->cast){
        case INT:   
	    return t->ival;
	    break;
	case DBL:
	    return t->rval;
	    break;
	case STR:
	    return t->sval;
	    break;
        default:
            return "Error";
    }

}

int getTypeCast(type_t *t){return t->cast;}
void printType(FILE *fp, type_t *t){

	switch (t->cast)
	{
		case INT:
			printInteger(fp, getTypeValue(t));
			break;
		
		case DBL:
			printReal(fp, getTypeValue(t));
			break;
		
		case STR:
			printString(fp, getTypeValue(t));
			break;
	
		default:
			break;
	}

}
/*** PRIVATE FUNCTION DEFINITIONS ***/
//parse token by char to determine type
int parseToken(void *item){

    char *token = (char *) item;
    int isint = 1;
    int isreal = 1;
    int dot = 0;
    int size = strlen(token);
    int i;
    for(i = 0; i < size; i++){
        if(isalpha(token[i])){
		    isreal = 0;
	    	isint = 0;
	    	break;
		}
		else if(token[i] == '.' && size == 1){
			isint = 0;
			isreal = 0;
			break;
		}
		else if(!isdigit(token[i])){
            if(token[i] == '.' && dot == 1){ 
				isreal = 0;
				isint = 0;
				break;
	    	}
        	else if(token[i] == '.') dot = 1;
	    	else if(i == 0 && token[i] != '-'){
                isreal = 0;
	    	    isint = 0;
				break;
        	}
	    	else{
	        	isreal = 0;
				isint = 0;
				break;
	    	}
		}
    }
    if(dot) isint = 0;
    else isreal = 0;

    if(isint) return INT;
    else if(isreal) return DBL;
    else return STR;

}

