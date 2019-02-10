/*****************************************************************************/
// env.c by Murray Estes
// An environment structure ISO scoping and variable input for ESL.
// Begin Date: 20190205
// Complete Date: 
/*****************************************************************************/
// Public Method Usage:
// lexeme_t *newEnv(void); 
// 	creates a new environment object
// 		lexeme_t *env = newEnv();
//
// type_t *lookup(lexeme_t *var, lexeme_t *env); 
// 	returns the value of a variable which has been defined in the current 
// 	environment scope.
// 		type_t *val = lookup(var, env);
//
// void update(lexeme_t *var, lexeme_t *val, lexeme_t *env);
// 	Updates the supplied variable name with the given value in the current
// 	scope.
// 		update(var, val, env);
//
// void insert(lexeme_t *var, lexeme_t *val, lexeme_t *env);
// 	Inserts a new variable and value into the current environment scope.
// 		insert(var, val, env);
//
// void extend(lexeme_t *var, lexeme_t *val, lexeme_t *env);
// 	Creates a new level of scope for the supplied environment and inserts
// 	the supplied variable and value.
// 		extend(var, val, env);
//
/*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "env.h"
#include "../type/type.h"
#include "../lex/lexeme.h"

#define TRUE 1
#define FALSE 0


/*** PRIVATE FUNCTION DECLARATIONS ***/
int same(lexeme_t *, lexeme_t *);

/*** PUBLIC FUNCTION DEFINITONS ***/
lexeme_t *newEnv(void){return cons(ENV, NULL, cons(VALUE, NULL, NULL));}
lexeme_t *lookup(lexeme_t *var, lexeme_t *env){

    while(env){
        lexeme_t *vars = car(env);
	    lexeme_t *val = car(cdr(env));
	    while(vars){
            if(same(var, car(vars))) return car(val);
	        vars = cdr(vars);
	        val = cdr(val);
	    }
	env = cdr(cdr(env));
    }

    fprintf(stderr, "Error: Variable ");
    printLexeme(stderr, var);
    fprintf(stderr, " is undefined or out of scope.\n");
    exit(-1);
    return NULL;

}

lexeme_t *update(lexeme_t *var, lexeme_t *val, lexeme_t *env){

    while(env){
        lexeme_t *vars = car(env);
	    lexeme_t *vals = car(cdr(env));
	    while(vars){
            if(same(var, car(vars))){
                setCar(val, vals);
		        return val;
	        }
	    vars = cdr(vars);
	    vals = cdr(vals);
	    }
	env = cdr(cdr(env));
    }

    fprintf(stderr, "Error: variable ");
    printLexeme(stderr, var);
    fprintf(stderr, " is undefined or out of scope.\n");
    exit(-1);
    return NULL;

}

lexeme_t *insert(lexeme_t *var, lexeme_t *val, lexeme_t *env){

    setCar(cons(JOIN, var, car(env)), env);
    setCar(cons(JOIN, val, car(cdr(env))), cdr(env));

    return car(env);
}

lexeme_t *extend(lexeme_t *var, lexeme_t *val, lexeme_t *env){
    return cons(ENV, var, cons(ENV, val, env));
}

void print_env(FILE *fp, lexeme_t *env, int local_flag){
    
    int env_lvl = 0;
    if(local_flag == TRUE) fprintf(fp, "The local environment is...\n");
    else fprintf(fp, "The full environment is...\n");
    while(env){
        lexeme_t *vars = car(env);
	    lexeme_t *val = car(cdr(env));
        if(local_flag == FALSE) fprintf(fp, "Environment: %d\n", env_lvl++);
        if(car(vars) == NULL){
            fprintf(fp, "void\n");
            env = cdr(cdr(env));
            if(local_flag == FALSE) continue;
            else break;
        }
	    while(vars){
            if(car(vars)){
                printLexeme(fp, car(vars));
                fprintf(fp, " = ");
                if(getLexemeValue(car(val))) printLexeme(fp, car(val));
                else fprintf(fp, "unassigned");
                fprintf(fp, "\n");
            }
	        vars = cdr(vars);
	        val = cdr(val);
	    }
	if(local_flag == FALSE) env = cdr(cdr(env));
    else break;

    }

}
/*** PRIVATE FUNCTION DEFINITONS ***/
int same(lexeme_t *a, lexeme_t *b){

    if(!a || !b) return FALSE;
    type_t *at = getLexemeValue(a);
    type_t *bt = getLexemeValue(b);
    int ac = getTypeCast(at);
    int bc = getTypeCast(bt);
    integer_t *ai, *bi;
    real_t *ar, *br;
    string_t *as, *bs;
    if(ac == bc){
        switch(ac){
            case INT:
                ai = getTypeValue(at);
		        bi = getTypeValue(bt);
		        if(compareInteger(ai, bi) == 0) return TRUE;
		        else return FALSE;
            case DBL:
		        ar = getTypeValue(at);
		        br = getTypeValue(bt);
		        if(compareReal(ar, br) == 0) return TRUE;
		        else return FALSE;
	        case STR:
		        as = getTypeValue(at);
		        bs = getTypeValue(bt);
		        if(compareString(as, bs) == 0) return TRUE;
		        else return FALSE;
            default:
		        return FALSE;
        }
    }
    else return FALSE;

}
