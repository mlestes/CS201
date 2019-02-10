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

/*** DEFINES ***/
//literals
#define INTEGER             0
#define REAL                1
#define STRING              2

//operators & general punctuation
#define OPEN_PAREN          3   // (
#define CLOSE_PAREN         4   // )
#define PLUS                5   // +
#define MINUS               6   // -
#define TIMES               7   // *
#define DIVIDE              8   // /
#define MOD                 9   // %
#define POW                 10  // ^
#define PLUS_PLUS           11  // ++
#define MINUS_MINUS         12  // --
#define ASSIGN              13  // =
#define STAR                14  // *
#define ADDRESS             15  // &
#define COLON               16  // :
#define SEMI_COLON          17  // ;
#define QUESTION            18  // ? <-ternary
#define DOT                 19  // .

//comparators
#define GREATER_THAN        20  // >
#define LESS_THAN           21  // <
#define GREATER_THAN_EQUALS 22  // >=
#define LESS_THAN_EQUALS    23  // <=
#define EQUALS_EQUALS       24  // ==

//logic
#define NOT                 25  // !
#define AND                 26  // AND
#define OR                  27  // OR
#define XOR                 28  // XOR

//keywords
#define VARIABLE            29
#define ERROR               30
#define IF                  31
#define ELSE                32
#define END                 33
#define BEGIN               34
#define RETURN              35
#define BREAK               36
#define CONTINUE            37
#define STRUCT              38
#define VAR                 39
#define DEFINE              40
#define PRINT               41
#define WHILE               42
#define END_READ            43

typedef struct Lexeme_Type lexeme_t;

extern lexeme_t *newLexeme(char *);
extern int getLexemeType(lexeme_t *);
extern type_t *getLexemeValue(lexeme_t *);
extern void setLexemeType(int, lexeme_t *);
extern void setLexemeValue(char *, lexeme_t *);
extern void setLexemeError(char *, lexeme_t *);
extern void setLexemeLeft(lexeme_t *, lexeme_t *);
extern lexeme_t *getLexemeLeft(lexeme_t *);
extern void setLexemeRight(lexeme_t *, lexeme_t *);
extern lexeme_t *getLexemeRight(lexeme_t *);
extern void printLexeme(FILE *, lexeme_t *);
extern lexeme_t *cons(int, lexeme_t *, lexeme_t *);
extern lexeme_t *car(lexeme_t *);
extern lexeme_t *cdr(lexeme_t *);
extern void setCar(lexeme_t *, lexeme_t *);
extern void setCdr(lexeme_t *, lexeme_t *);

#endif
