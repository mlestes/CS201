/*****************************************************************************/
// parse.c by Murray Estes
// Parsing functions iso parsing source code of ESL.
// Begin Date: 20190124
// Complete Date:
/*****************************************************************************/
// Usage (Command line)
// recognizer <file name>
/*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parse.h"
#include "../lex/lexeme.h"
#include "../lex/lexer.h"
#include "../type/type.h"
#include "../type/str.h"

#define TRUE 1
#define FALSE 0

/*** GLOBALS ***/
extern FILE *fp;
extern lexeme_t *current;
extern lexeme_t *env;
extern int line;

/*** PRIVATE FUNCTION DECLARATIONS ***/
//none

/*** MAIN/PUBLIC FUNCTION DEFINITITIONS ***/
lexeme_t *advance(void){

    lexeme_t *prev = current;
    current = lex(fp);
    return prev;

}

lexeme_t *match(int type){

    if(check(type)) return advance();
    else return parse_error(type);

}

int check(int type){

    int l_type = getLexemeType(current);
    if(type == l_type) return TRUE;
    else return FALSE;

}

lexeme_t *parse_error(int type){

    char *str, *err_str;
    int err_type = getLexemeType(current);
    switch(type){
        case INTEGER: str = "INTEGER"; break;
        case REAL: str = "REAL"; break;
        case STRING: str = "STRING"; break;
        case OPEN_PAREN: str = "OPEN_PAREN"; break;
        case CLOSE_PAREN: str = "CLOSE_PAREN"; break;
        case PLUS: str = "PLUS"; break;
        case MINUS: str = "MINUS"; break;
        case TIMES: str = "TIMES"; break;
        case DIVIDE: str = "DIVIDE"; break;
        case MOD: str = "MOD"; break;
        case POW: str = "POW"; break;
        case PLUS_PLUS: str = "PLUS_PLUS"; break;
        case MINUS_MINUS: str = "MINUS_MINUS"; break;
        case ASSIGN: str = "ASSIGN"; break;
        case STAR: str = "STAR"; break;
        case ADDRESS: str = "ADDRESS"; break;
        case COLON: str = "COLON"; break;
        case SEMI_COLON: str = "SEMI_COLON"; break;
        case QUESTION: str = "QUESTION"; break;
        case DOT: str = "DOT"; break;
        case GREATER_THAN: str = "GREATER_THAN"; break;
        case LESS_THAN: str = "LESS_THAN"; break;
        case GREATER_THAN_EQUALS: str = "GREATER_THAN_EQUALS"; break;
        case LESS_THAN_EQUALS: str = "LESS_THAN_EQUALS"; break;
        case EQUALS_EQUALS: str = "EQUALS_EQUALS"; break;
        case NOT: str = "NOT"; break;
        case AND: str = "AND"; break;
        case OR: str = "OR"; break;
        case XOR: str = "XOR"; break;
        case VARIABLE: str = "VARIABLE"; break;
        case IF: str = "IF"; break;
        case ELSE: str = "ELSE"; break;
        case END: str = "END"; break;
        case BEGIN: str = "BEGIN"; break;
        case END_READ: str = "END_READ"; break;
        case PROGRAM: str = "PROGRAM"; break;
        case BLOCK: str = "BLOCK"; break;
        case EXPR: str = "EXPR"; break;
        case OPERATOR: str = "OPERATOR"; break;
        case COMPARATOR: str = "COMPARATOR"; break;
        case LOGIC: str = "LOGIC"; break;
        default: str = "UNKNOWN";

    }
    switch(err_type){
        case INTEGER: err_str = "INTEGER"; break;
        case REAL: err_str = "REAL"; break;
        case STRING: err_str = "STRING"; break;
        case OPEN_PAREN: err_str = "OPEN_PAREN"; break;
        case CLOSE_PAREN: err_str = "CLOSE_PAREN"; break;
        case PLUS: err_str = "PLUS"; break;
        case MINUS: err_str = "MINUS"; break;
        case TIMES: err_str = "TIMES"; break;
        case DIVIDE: err_str = "DIVIDE"; break;
        case MOD: err_str = "MOD"; break;
        case POW: err_str = "POW"; break;
        case PLUS_PLUS: err_str = "PLUS_PLUS"; break;
        case MINUS_MINUS: err_str = "MINUS_MINUS"; break;
        case ASSIGN: err_str = "ASSIGN"; break;
        case STAR: err_str = "STAR"; break;
        case ADDRESS: err_str = "ADDRESS"; break;
        case COLON: err_str = "COLON"; break;
        case SEMI_COLON: err_str = "SEMI_COLON"; break;
        case QUESTION: err_str = "QUESTION"; break;
        case DOT: err_str = "DOT"; break;
        case GREATER_THAN: err_str = "GREATER_THAN"; break;
        case LESS_THAN: err_str = "LESS_THAN"; break;
        case GREATER_THAN_EQUALS: err_str = "GREATER_THAN_EQUALS"; break;
        case LESS_THAN_EQUALS: err_str = "LESS_THAN_EQUALS"; break;
        case EQUALS_EQUALS: err_str = "EQUALS_EQUALS"; break;
        case NOT: err_str = "NOT"; break;
        case AND: err_str = "AND"; break;
        case OR: err_str = "OR"; break;
        case XOR: err_str = "XOR"; break;
        case VARIABLE: err_str = "VARIABLE"; break;
        case IF: err_str = "IF"; break;
        case ELSE: err_str = "ELSE"; break;
        case END: err_str = "END"; break;
        case BEGIN: err_str = "BEGIN"; break;
        case END_READ: err_str = "END_READ"; break;
        case PROGRAM: err_str = "PROGRAM"; break;
        case BLOCK: err_str = "BLOCK"; break;
        case EXPR: err_str = "EXPR"; break;
        case OPERATOR: err_str = "OPERATOR"; break;
        case COMPARATOR: err_str = "COMPARATOR"; break;
        case LOGIC: err_str = "LOGIC"; break;
        case RETURN: err_str = "RETURN"; break;
        case BREAK: err_str = "BREAK"; break;
        case CONTINUE: err_str = "CONTINUE"; break;
        case STRUCT: err_str = "STRUCT"; break;
        case VAR: err_str = "VAR"; break;
        case DEFINE: err_str = "DEFINE"; break;
        case PRINT: err_str = "PRINT"; break;
        case WHILE: err_str = "WHILE"; break;
        default: err_str = "UNKNOWN";

    }
    fprintf(stderr, "Line %d: Error: Expected type %s. Instead got type %s.\n"
		    "The invalid token is \"", line, str, err_str);
    printLexeme(stderr, current);
    fprintf(stderr, "\"\n");
    exit(-1);

    return 0;

}

lexeme_t *program(void){

//determine which rule to use
    lexeme_t *l; lexeme_t *r;
    if(funcdef_pending()) l = funcdef();
    else if(vardef_pending()) l = vardef();
    else if(structdef_pending()) l = structdef();
    else l = NULL; //either blank file or invalid file
    if(program_pending()) r = program();
    else r = NULL;

    return cons(PROGRAM, l, r);

}

int program_pending(void){

    if(funcdef_pending() || vardef_pending() || structdef_pending())
        return TRUE;
    else return FALSE;

}

lexeme_t *funcdef(void){

    lexeme_t *l, *r1, *r2;
    match(DEFINE);
    l = match(VARIABLE);
    match(OPEN_PAREN);
    if(parameterlist_pending()) r1 = parameterlist();
    else r1 = NULL;
    match(CLOSE_PAREN);
    r2 = block();

    return cons(DEFINE, l, cons(FUNCDEF, r1, r2));

}

int funcdef_pending(void){

    if(check(DEFINE)) return TRUE;
    else return FALSE;

}

lexeme_t *vardef(void){

    lexeme_t *l, *r;
    match(VAR);
    l = match(VARIABLE);
    if(check(ASSIGN)){
        match(ASSIGN);
        r = expression();
    }
    else r = NULL;
    match(SEMI_COLON);

    return cons(VAR, l, r);

}

int vardef_pending(void){

    if(check(VAR)) return TRUE;
    else return FALSE;

}

lexeme_t *structdef(void){

    lexeme_t *l; lexeme_t *r;
    match(STRUCT);
    l = match(VARIABLE);
    r = block();

    return cons(STRUCT, l, r);

}

int structdef_pending(void){

    if(check(STRUCT)) return TRUE;
    else return FALSE;

}

lexeme_t *parameterlist(void){

    lexeme_t *l; lexeme_t *r;
    l = match(VARIABLE);
    if(parameterlist_pending()) r = parameterlist();
    else r = NULL;

    return cons(PARAM_LIST, l, r);

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
	    //match(SEMI_COLON);
    }
    else if(funcdef_pending()) l = funcdef();
    else if(ifstate_pending()) l = ifstate();
    else if(whilestate_pending()) l = whilestate();

    return cons(STATEMENT, l, NULL);

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

    return cons(STATE_LIST, l, r);

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

    return cons(BLOCK, l, NULL);

}

int block_pending(void){

    if(check(BEGIN)) return TRUE;
    else return FALSE;

}

lexeme_t *whilestate(void){

    lexeme_t *l; lexeme_t *r;
    match(WHILE);
    match(OPEN_PAREN);
    l = expression();
    match(CLOSE_PAREN);
    r = block();

    return cons(WHILE, l, r);

}

int whilestate_pending(void){

    if(check(WHILE)) return TRUE;
    else return FALSE;

}

lexeme_t *elsestate(void){

    lexeme_t *l;
    match(ELSE);
    l = block();

    return cons(ELSE, l, NULL);

}

int elsestate_pending(void){

    if(check(ELSE)) return TRUE;
    else return FALSE;

}

lexeme_t *ifstate(void){

    lexeme_t *l, *r1, *r2;
    match(IF);
    match(OPEN_PAREN);
    l = expression();
    match(CLOSE_PAREN);
    r1 = block();
    if(elsestate_pending()) r2 = elsestate();
    else r2 = NULL;

    return cons(IF, l, cons(JOIN, r1, r2));

}

int ifstate_pending(void){

    if(check(IF)) return TRUE;
    else return FALSE;

}

lexeme_t *suffix(void){

    lexeme_t *l;
    if(check(PLUS_PLUS)) l = match(PLUS_PLUS);
    else l = match(MINUS_MINUS);

    return cons(SUFFIX, l, NULL);

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

    return cons(PREFIX, l, NULL);

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

    return cons(LOGIC, l, NULL);

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

    return cons(COMPARATOR, l, r);

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

    return cons(OPERATOR, l, NULL);

}

int operator_pending(void){

    if(check(PLUS) || check(MINUS) || check(TIMES) || check(DIVIDE) ||
       check(MOD) || check(POW) || check(ASSIGN) || check(DOT) || 
       check(QUESTION) || check(COLON)) return TRUE;
    else return FALSE;

}

lexeme_t *printstatement(void){
 
    lexeme_t *l; lexeme_t *r;
    l = unary();
    if(printstatement_pending()) r = printstatement();
    else r = NULL;

    return cons(PRINT_STATE, l, r);

}

int printstatement_pending(void){

    if(check(STRING) || check(VARIABLE)) return TRUE;
    else return FALSE;

}

lexeme_t *expressionlist(void){

    lexeme_t *l; lexeme_t *r;
    l = expression();
    if(expressionlist_pending()) r = expressionlist();
    else r = NULL;

    return cons(EXPR_LIST, l, r);

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
    }
    else if(comparator_pending()){
	    op = comparator();
    }
    else if(logic_pending()){
	op = logic();
    }
    else{
	op = NULL;
    }
    if(expression_pending()) r = expression();
    else r = NULL;

    return cons(EXPR, l, cons(EXPR, op, r));

}

int expression_pending(void){

    if(unary_pending()) return TRUE;
    else return FALSE;

}

lexeme_t *unary(void){

    lexeme_t *l; lexeme_t *r = NULL;
    if(check(STRING)) l = match(STRING);
    else if(check(INTEGER)) l = match(INTEGER);
    else if(check(REAL)) l = match(REAL);
    else if(check(VARIABLE)){
        l = match(VARIABLE);
	    if(check(OPEN_PAREN)){
            match(OPEN_PAREN);
            if(expressionlist_pending()) r = expressionlist();
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

    return cons(UNARY, l, r);

}

int unary_pending(void){

    if(check(INTEGER) || check(REAL) || check(STRING) || check(VARIABLE) ||
       check(OPEN_PAREN) || check(PRINT) || check(RETURN) || check(BREAK) ||
       check(CONTINUE) || prefix_pending()) return TRUE;
    else return FALSE;

}

/*** PRIVATE FUNCTION DEFINITIONS ***/
//none
