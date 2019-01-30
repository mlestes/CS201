/*****************************************************************************/
// recognizer.c by Murray Estes
// A recognizer iso parsing source code of ESL.
// Begin Date: 20190124
// Complete Date:
/*****************************************************************************/
// Usage (Command line)
// recognizer <file name>
/*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexeme.h"
#include "lexer.h"
#include "type.h"
#include "str.h"

#define TRUE 1
#define FALSE 0

/*** GLOBALS ***/
FILE *fp;
lexeme_t *current;
int line = 1;

/*** PRIVATE FUNCTION DECLARATIONS ***/
lexeme_t *advance(void);
lexeme_t *match(char *);
int check(char *);
lexeme_t *parse_error(char *);
lexeme_t *program(void);
int program_pending(void);
lexeme_t *funcdef(void);
int funcdef_pending(void);
lexeme_t *vardef(void);
int vardef_pending(void);
lexeme_t *structdef(void);
int structdef_pending(void);
lexeme_t *parameterlist(void);
int parameterlist_pending(void);
lexeme_t *block(void);
int block_pending(void);
lexeme_t *statementlist(void);
int statementlist_pending(void);
lexeme_t *statement(void);
int statement_pending(void);
lexeme_t *whilestate(void);
int whilestate_pending(void);
lexeme_t *ifstate(void);
int ifstate_pending(void);
lexeme_t *elsestate(void);
int elsestate_pending(void);
lexeme_t *suffix(void);
int suffix_pending(void);
lexeme_t *prefix(void);
int prefix_pending(void);
lexeme_t *logic(void);
int logic_pending(void);
lexeme_t *comparator(void);
int comparator_pending(void);
lexeme_t *operator(void);
int operator_pending(void);
lexeme_t *printstatement(void);
int printstatement_pending(void);
lexeme_t *expressionlist(void);
int expressionlist_pending(void);
lexeme_t *expression(void);
int expression_pending(void);
lexeme_t *unary(void);
int unary_pending(void);
lexeme_t *construct(lexeme_t *, lexeme_t *, lexeme_t *);

/*** MAIN/PUBLIC FUNCTION DEFINITITIONS ***/
int main(int argc, char **argv){

    //check for correct number of inputs
    if(argc < 2){ //too few inputs
        fprintf(stderr, "Error: incorrect number of inputs.\n"
                        "Usage: ./recognizer <file>\n");
	exit(-1);
    }

    //attempt to open the file
    fp = fopen(argv[1], "r");
    if(!fp){ //attempt failed
        fprintf(stderr, "Error: could not open file \"%s\".\n"
			"File either missing or spelled incorrectly.\n", 
			argv[1]);
	exit(-1);
    }

    //check if file extension is .esl
    int len = strlen(argv[1]) - 1;
    char *name = argv[1];
    if(name[len-3] != '.' || name[len-2] != 'e' || name[len-1] != 's' || 
       name[len] != 'l'){
        fprintf(stderr, "Error: unrecognized file type. File must be of "
			"extension \".esl\"\n");
	exit(-1);
    }

    //read the source code, stopping at either EOF or error
    current = lex(fp);
    program();
    match(END_READ);
    fprintf(stdout, "Parse complete. No errors.\n");
    fclose(fp);

    return 0;

}

/*** PRIVATE FUNCTION DEFINITIONS ***/
lexeme_t *advance(void){

    lexeme_t *prev = current;
    current = lex(fp);
    return prev;

}

lexeme_t *match(char *type){

    if(check(type)) return advance();
    else return parse_error(type);

}

int check(char *type){

    char *l_type = getLexemeType(current);
    if(strcmp(type, l_type) == 0) return TRUE;
    else return FALSE;

}

lexeme_t *parse_error(char *type){

    char *err_type = getLexemeType(current);
    fprintf(stderr, "Line %d: Error: Expected type %s. Instead got type %s.\n"
		    "The invalid token is \"", line, type, err_type);
    printLexeme(stderr, current);
    fprintf(stderr, "\"\n");
    exit(-1);

    return 0;

}

lexeme_t *construct(lexeme_t *type, lexeme_t *left, lexeme_t *right){

    //check if type is NULL
    if(!type) return NULL;
    //it's not NULL, so check if keyword
    char *l_type = getLexemeType(type);
    type_t *l_value = getLexemeValue(type);
    string *s = getTypeValue(l_value);
    char *val = getString(s);
    //if not a keyword, set the type to match the value
    if(strcmp(val, l_type)) setLexemeType(val, type);
    setLexemeLeft(type, left);
    setLexemeRight(type, right);
    return type;

}

lexeme_t *program(void){

//determine which rule to use
    lexeme_t *l; lexeme_t *r;
    if(funcdef_pending()) l = funcdef();
    else if(vardef_pending()) l = vardef();
    else if(structdef_pending()) l = structdef();
    else l = NULL;

//determine if another program rule follows
    if(program_pending()) r = program();
    else r = NULL;

//return the new lexeme
    return construct(newLexeme("program"), l, r);

}

int program_pending(void){

    if(funcdef_pending() || vardef_pending() || structdef_pending())
        return TRUE;
    else return FALSE;

}

lexeme_t *funcdef(void){

    lexeme_t *v; lexeme_t *l; lexeme_t *r;
    v = match(DEFINE);
    l = match(VARIABLE);
    if(check(OPEN_PAREN)){
        match(OPEN_PAREN);
        parameterlist();
	match(CLOSE_PAREN);
	r = block();
    }
    else{
        match(SEMI_COLON);
	r = NULL;
    }

    return construct(v, l, r);

}

int funcdef_pending(void){

    if(check(DEFINE)) return TRUE;
    else return FALSE;

}

lexeme_t *vardef(void){

    lexeme_t *v; lexeme_t *l; lexeme_t *r;
    v = match(VAR);
    l = match(VARIABLE);
    if(check(ASSIGN)){
        advance();
	r = expression();
    }
    else{
	r = NULL;
    }
    match(SEMI_COLON);

    return construct(v, l, r);

}

int vardef_pending(void){

    if(check(VAR)) return TRUE;
    else return FALSE;

}

lexeme_t *structdef(void){

    lexeme_t *v; lexeme_t *l; lexeme_t *r;
    v = match(STRUCT);
    l = match(VARIABLE);
    r = block();

    return construct(v, l, r);

}

int structdef_pending(void){

    if(check(STRUCT)) return TRUE;
    else return FALSE;

}

lexeme_t *parameterlist(void){

    lexeme_t *l; lexeme_t *r;
    if(check(VARIABLE)) l = match(VARIABLE);
    else l = NULL;
    if(parameterlist_pending()) r = parameterlist();
    else r = NULL;

    return construct(newLexeme("parameterlist"), l, r);

}

int parameterlist_pending(void){

    if(check(VARIABLE)) return TRUE;
    else return FALSE;

}

lexeme_t *statement(void){

    lexeme_t *l;
    if(expression_pending()){
        l = expression();
	match(SEMI_COLON);
    }
    else if(vardef_pending()){
        l = vardef();
    }
    else if(funcdef_pending()) l = funcdef();
    else if(ifstate_pending()) l = ifstate();
    else if(whilestate_pending()) l = whilestate();

    return construct(newLexeme("statement"), l, NULL);

}

int statement_pending(void){

    if(expression_pending() || vardef_pending() || funcdef_pending() || 
       ifstate_pending() || whilestate_pending()) return TRUE;
    else return FALSE;

}

lexeme_t *statementlist(void){

    lexeme_t *l; lexeme_t *r;
    l = statement();
    if(statementlist_pending()) r = statementlist();
    else r = NULL;

    return construct(newLexeme("statementlist"), l, r);

}

int statementlist_pending(void){

    if(statement_pending()) return TRUE;
    else return FALSE;

}

lexeme_t *block(void){

    lexeme_t *l;
    match(BEGIN);
    l = statementlist();
    match(END);

    return construct(newLexeme("block"), l, NULL);

}

int block_pending(void){

    if(check(BEGIN)) return TRUE;
    else return FALSE;

}

lexeme_t *whilestate(void){

    lexeme_t *v; lexeme_t *l; lexeme_t *r;
    v = match(WHILE);
    match(OPEN_PAREN);
    l = expression();
    match(CLOSE_PAREN);
    r = block();

    return construct(v, l, r);

}

int whilestate_pending(void){

    if(check(WHILE)) return TRUE;
    else return FALSE;

}

lexeme_t *elsestate(void){

    lexeme_t *v; lexeme_t *l;
    if(check(ELSE)){
        v = match(ELSE);
        l = block();
    }
    else{
	v = NULL;
	l = NULL;
    }

    return construct(v, l, NULL);

}

int elsestate_pending(void){

    if(check(ELSE)) return TRUE;
    else return FALSE;

}

lexeme_t *ifstate(void){

    lexeme_t *v; lexeme_t *l; lexeme_t *r;
    v = match(IF);
    match(OPEN_PAREN);
    l = expression();
    match(CLOSE_PAREN);
    block();
    if(elsestate_pending()) r = elsestate();
    else r = NULL;

    return construct(v, l, r);

}

int ifstate_pending(void){

    if(check(IF)) return TRUE;
    else return FALSE;

}

lexeme_t *suffix(void){

    lexeme_t *l;
    if(check(PLUS_PLUS)) l = match(PLUS_PLUS);
    else l = match(MINUS_MINUS);

    return construct(newLexeme("suffix"), l, NULL);

}

int suffix_pending(void){

    if(check(PLUS_PLUS) || check(MINUS_MINUS)) return TRUE;
    else return FALSE;

}

lexeme_t *prefix(void){

    lexeme_t *l;
    if(check(PLUS)) l = match(PLUS);
    else if(check(MINUS)) l = match(MINUS);
    else if(check(PLUS_PLUS)) l = match(PLUS_PLUS);
    else if(check(MINUS_MINUS)) l = match(MINUS_MINUS);
    else if(check(ADDRESS)) l = match(ADDRESS);
    else l = match(STAR);

    return construct(newLexeme("prefix"), l, NULL);

}

int prefix_pending(void){

    if(check(PLUS) || check(MINUS) || check(PLUS_PLUS) || check(MINUS_MINUS)
       || check(ADDRESS) || check(STAR)) return TRUE;
    else return FALSE;

}

lexeme_t *logic(void){

    lexeme_t *l;
    if(check(AND)) l = match(AND);
    else if(check(OR)) l = match(OR);
    else l = match(XOR);

    return construct(newLexeme("logic"), l, NULL);

}

int logic_pending(void){

    if(check(AND) || check(OR) || check(XOR)) return TRUE;
    else return FALSE;

}

lexeme_t *comparator(void){

    lexeme_t *l; lexeme_t *r = NULL;
    if(check(GREATER_THAN)) l = match(GREATER_THAN);
    else if(check(LESS_THAN)) l = match(LESS_THAN);
    else if(check(EQUALS_EQUALS)) l = match(EQUALS_EQUALS);
    else if(check(GREATER_THAN_EQUALS)) l = match(GREATER_THAN_EQUALS);
    else if(check(LESS_THAN_EQUALS)) l = match(LESS_THAN_EQUALS);
    else{
        l = match(NOT);
	r = comparator();
    }

    return construct(newLexeme("comparator"), l, r);

}

int comparator_pending(void){

    if(check(GREATER_THAN) || check(LESS_THAN) || check(EQUALS_EQUALS) ||
       check(GREATER_THAN_EQUALS) || check(LESS_THAN_EQUALS) || check(NOT))
       return TRUE;
    else return FALSE;

}

lexeme_t *operator(void){

    lexeme_t *l;
    if(check(PLUS)) l = match(PLUS);
    else if(check(MINUS)) l = match(MINUS);
    else if(check(TIMES)) l = match(TIMES);
    else if(check(DIVIDE)) l = match(DIVIDE);
    else if(check(MOD)) l = match(MOD);
    else if(check(POW)) l = match(POW);
    else if(check(ASSIGN)) l = match(ASSIGN);
    else if(check(QUESTION)) l = match(QUESTION);
    else if(check(COLON)) l = match(COLON);
    else l = match(DOT);

    return construct(newLexeme("operator"), l, NULL);

}

int operator_pending(void){

    if(check(PLUS) || check(MINUS) || check(TIMES) || check(DIVIDE) ||
       check(MOD) || check(POW) || check(ASSIGN) || check(DOT) || 
       check(QUESTION) || check(COLON)) return TRUE;
    else return FALSE;

}

lexeme_t *printstatement(void){
 
    lexeme_t *l; lexeme_t *r;
    if(check(STRING_)) l = match(STRING_);
    else if(unary_pending()) l = unary();
    if(printstatement_pending()) r = printstatement();
    else r = NULL;

    return construct(newLexeme("printstatement"), l, r);

}

int printstatement_pending(void){

    if(check(STRING_) || check(VARIABLE)) return TRUE;
    else return FALSE;

}

lexeme_t *expressionlist(void){

    lexeme_t *l; lexeme_t *r;
    if(expression_pending()) l = expression();
    else l = NULL;
    if(expressionlist_pending()) r = expressionlist();
    else r = NULL;

    return construct(newLexeme("expressionlist"), l, r);

}

int expressionlist_pending(void){

    if(expression_pending()) return TRUE;
    else return FALSE;

}

lexeme_t *expression(void){

    lexeme_t *op; lexeme_t *l; lexeme_t *r;
    l = unary();
    if(operator_pending()){
        op = operator();
	r = expression();
    }
    else if(comparator_pending()){
	op = comparator();
	r = expression();
    }
    else if(logic_pending()){
	op = logic();
	r = expression();
    }
    else{
	op = newLexeme("expression");
	r = NULL;
    }

    return construct(op, l, r);

}

int expression_pending(void){

    if(unary_pending()) return TRUE;
    else return FALSE;

}

lexeme_t *unary(void){

    lexeme_t *l; lexeme_t *r = NULL;
    if(check(STRING_)) l = match(STRING_);
    else if(check(INTEGER_)) l = match(INTEGER_);
    else if(check(REAL_)) l = match(REAL_);
    else if(check(VARIABLE)){
        l = match(VARIABLE);
	if(check(OPEN_PAREN)){
            match(OPEN_PAREN);
            r = expressionlist();
	    match(CLOSE_PAREN);
	}
	else if(suffix_pending()) r = suffix();
    }
    else if(check(OPEN_PAREN)){
        match(OPEN_PAREN);
	l = expression();
	match(CLOSE_PAREN);
    }
    else if(check(PRINT)){
	l = match(PRINT);
	match(OPEN_PAREN);
        r = printstatement();
	match(CLOSE_PAREN);
    }
    else if(check(RETURN)){
	l = match(RETURN);
	r = expression();
    }
    else if(check(BREAK)) l = match(BREAK);
    else if(prefix_pending()){
        l = prefix();
	r = unary();
    }
    else l = match(CONTINUE);

    return construct(newLexeme("unary"), l, r);

}

int unary_pending(void){

    if(check(INTEGER_) || check(REAL_) || check(STRING_) || check(VARIABLE) ||
       check(OPEN_PAREN) || check(PRINT) || check(RETURN) || check(BREAK) ||
       check(CONTINUE) || prefix_pending()) return TRUE;
    else return FALSE;

}
