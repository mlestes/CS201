/*****************************************************************************/
// lexeme.c by Murray Estes
// Implements a lexeme class for a custom language
// Begin Date: 20190117
// Complete Date:
/*****************************************************************************/
// Usage:
// lexeme_t *newLexeme(char *) - creates a new lexeme object
//     lexeme_t *l = newLexeme("test");
//
// char *getLexemeType(lexeme_t *) - retrieves the type of lexeme
//     char *type = getLexemeType(l);
//
// type_t *getLexemeValue(lexeme_t *) - returns the type object within the
//                                      lexeme object
//     type_t *t = getLexemeValue(l);
//
/*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexeme.h"
#include "type.h"
#include "str.h"
#include "real.h"
#include "int.h"

/*** STRUCTURE ***/
struct Lexeme_Type{

	char *type;
	type_t *value;
	char *error;

};

/*** PRIVATE FUNCTION DECLARATIONS ***/
char *parse(char *);
int hasdot(char *);

/*** PUBLIC/MAIN FUNCTION DEFINITIONS ***/
lexeme_t *newLexeme(char *item){

	lexeme_t *l = malloc(sizeof(lexeme_t));
	l->value = newType(item);
	l->type = parse(item);
	l->error = 0;

	return l;

}

char *getLexemeType(lexeme_t *l){return l->type;}
type_t *getLexemeValue(lexeme_t *l){return l->value;}
void setLexemeType(char *type, lexeme_t *l){l->type = type;}
void setLexemeValue(char *val, lexeme_t *l){l->value = newType(val);}
void setLexemeError(char *err, lexeme_t *l){l->error = err;}
void printLexeme(FILE *fp, lexeme_t *l){

    string *s; integer *i; real *r;
    //handle error type first
    if(strcmp(l->type, "ERROR") == 0){
        string *e = getTypeValue(l->value);
        char *err_token = getString(e);
        fprintf(stderr, "%s\n\"%s\" is the invalid token.\n", 
                l->error, err_token);
        return ;
    }

    //normal type now
    int t = getTypeCast(l->value);
    switch(t){
        case STR:
            s = getTypeValue(l->value);
            printString(fp, s);
            fprintf(fp, "\t%s", l->type);
	    break;
        case INT:
            i = getTypeValue(l->value);
	    printInteger(fp, i);
	    fprintf(fp, "\t%s", l->type);
	    break;
        case DBL:
	    r = getTypeValue(l->value);
	    printReal(fp, r);
	    fprintf(fp, "\t%s", l->type);
	    break;
    }

}

/*** PRIVATE FUNCTION DEFINITIONS ***/
char *parse(char *str){

    int size = strlen(str);
    char c = str[0];
    if(isdigit(c)){
        if(hasdot(str)) return REAL_;
        else return INTEGER_;
    }
    switch(size){
        case 1:
            if(c == '(') return OPEN_PAREN;
	    else if(c == ')') return CLOSE_PAREN;
	    else if(c == '+') return PLUS;
	    else if(c == '-') return MINUS;
	    else if(c == '/') return DIVIDE;
	    else if(c == '*') return TIMES;
	    else if(c == '!') return NOT;
	    else if(c == '>') return GREATER_THAN;
	    else if(c == '<') return LESS_THAN;
	    else if(c == '=') return ASSIGN;
	    else if(c == '%') return MOD;
	    else if(c == '^') return POW;
	    else if(c == '.') return DOT;
	    else if(c == '?') return QUESTION;
	    else if(c == ';') return SEMI_COLON;
	    else if(c == ':') return COLON;
	    else if(c == '&') return ADDRESS;
	    else return STRING_;
	    break;
	case 2:
	    if(strcmp(str, "++") == 0) return PLUS_PLUS;
	    else if(strcmp(str, "--") == 0) return MINUS_MINUS;
	    else if(strcmp(str, "==") == 0) return EQUALS_EQUALS;
	    else if(strcmp(str, ">=") == 0) return GREATER_THAN_EQUALS;
	    else if(strcmp(str, "<=") == 0) return LESS_THAN_EQUALS;
	    else if(strcmp(str, "OR") == 0) return OR;
	    else if(strcmp(str, "IF") == 0) return IF;
	    else return STRING_;
	    break;
	case 3:
	    if(strcmp(str, "AND") == 0) return AND;
	    else if(strcmp(str, "XOR") == 0) return XOR;
	    else if(strcmp(str, "END") == 0) return END;
	    else if(strcmp(str, "VAR") == 0) return VAR;
            else return STRING_;
	    break;
	case 4:
	    if(strcmp(str, "ELSE") == 0) return ELSE;
	    else if(strcmp(str, "STAR") == 0) return STAR;
	    else return STRING_;
	    break;
	case 5:
	    if(strcmp(str, "WHILE") == 0) return WHILE;
	    else if(strcmp(str, "BREAK") == 0) return BREAK;
	    else if(strcmp(str, "BEGIN") == 0) return BEGIN;
	    else if(strcmp(str, "PRINT") == 0) return PRINT;
	    else return STRING_;
	    break;
	case 6:
	    if(strcmp(str, "STRUCT") == 0) return STRUCT;
	    else if(strcmp(str, "DEFINE") == 0) return DEFINE;
	    else if(strcmp(str, "RETURN") == 0) return RETURN;
	    else return STRING_;
	    break;
	default:
	    if(strcmp(str, "CONTINUE") == 0) return CONTINUE;
	    else return STRING_;
    }

}

int hasdot(char *str){

    int i = 0;
    int size = strlen(str);
    int dot = 0;
    while(i < size){
        if(str[i] == '.') dot = 1;
        i++;
    }

    return dot;

}
