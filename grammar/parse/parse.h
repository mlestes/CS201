/*****************************************************************************/
// parse.h by Murray Estes
// A header file for parsing function ISO implementing ESL.
/*****************************************************************************/

#ifndef __PARSE_H__
#define __PARSE_H__

#include "../lex/lexeme.h"

#define JOIN        -1
#define PROGRAM     200
#define BLOCK       201
#define PARAM_LIST  202
#define STATEMENT   203
#define STATE_LIST  204
#define SUFFIX      205
#define PREFIX      206
#define LOGIC       207
#define COMPARATOR  208
#define OPERATOR    209
#define PRINT_STATE 210
#define EXPR_LIST   211
#define EXPR        212
#define UNARY       213
#define FUNCDEF     214
#define VARDEF      215
#define STRUCTDEF   216

lexeme_t *advance(void);
lexeme_t *match(int);
int check(int);
lexeme_t *parse_error(int);
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

#endif
