/*****************************************************************************/
/* lex.h by Murray Estes                                                     */
/* Header file for implementing a lexeme class for ESL                       */
/* Begin date: 20190117                                                      */
/* Complete date:                                                            */
/*****************************************************************************/

#include <stdlib.h>
#include "../type/type.h"

#ifndef __LEXEME_H__
#define __LEXEME_H__

#define INTEGER_ "INTEGER"
#define REAL_ "REAL"
#define STRING_ "STRING"
#define OPEN_PAREN "OPEN_PAREN"
#define CLOSE_PAREN "CLOSE_PAREN"
#define PLUS "PLUS"
#define MINUS "MINUS"
#define TIMES "TIMES"
#define DIVIDE "DIVIDE"
#define MOD "MOD"
#define POW "POW"
#define PLUS_PLUS "PLUS_PLUS"
#define MINUS_MINUS "MINUS_MINUS"
#define ASSIGN "ASSIGN"
#define NOT "NOT"
#define GREATER_THAN "GREATER_THAN"
#define LESS_THAN "LESS_THAN"
#define GREATER_THAN_EQUALS "GREATER_THAN_EQUALS"
#define LESS_THAN_EQUALS "LESS_THAN_EQUALS"
#define EQUALS_EQUALS "EQUALS_EQUALS"
#define AND "AND"
#define OR "OR"
#define XOR "XOR"
#define VARIABLE "VARIABLE"
#define STAR "STAR"
#define ADDRESS "ADDRESS"
#define ERROR "ERROR"
#define IF "IF"
#define ELSE "ELSE"
#define END "END"
#define BEGIN "BEGIN"
#define RETURN "RETURN"
#define BREAK "BREAK"
#define CONTINUE "CONTINUE"
#define STRUCT "STRUCT"
#define VAR "VAR"
#define DEFINE "DEFINE"
#define PRINT "PRINT"
#define WHILE "WHILE"
#define COLON "COLON"
#define SEMI_COLON "SEMI_COLON"
#define QUESTION "QUESTION"
#define DOT "DOT"
#define END_READ "END_READ"

typedef struct Lexeme_Type lexeme_t;

extern lexeme_t *newLexeme(char *);
extern char *getLexemeType(lexeme_t *);
extern type_t *getLexemeValue(lexeme_t *);
extern void setLexemeType(char *, lexeme_t *);
extern void setLexemeValue(char *, lexeme_t *);
extern void setLexemeError(char *, lexeme_t *);
extern void setLexemeLeft(lexeme_t *, lexeme_t *);
extern lexeme_t *getLexemeLeft(lexeme_t *);
extern void setLexemeRight(lexeme_t *, lexeme_t *);
extern lexeme_t *getLexemeRight(lexeme_t *);
extern void printLexeme(FILE *, lexeme_t *);

#endif
