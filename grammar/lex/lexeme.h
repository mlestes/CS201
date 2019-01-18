/*****************************************************************************/
/* lex.h by Murray Estes                                                     */
/* Header file for implementing a designer language                          */
/* Begin date: 20190117                                                      */
/* Complete date:                                                            */
/*****************************************************************************/

#include <stdlib.h>
#include "type.h"

#ifndef __LEXEME_H__
#define __LEXEME_H__

#define INTEGER "INTEGER"
#define REAL "REAL
#define STRING "STRING"
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
#define ERROR "ERROR"

typedef struct lexeme;

extern struct lexeme newLexeme(char *);

#endif
