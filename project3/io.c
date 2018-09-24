#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
//LOCAL INCLUDES
#include "scanner.h"
#include "io.h"

/*****************************************************************************/
/* io.c BY Murray Estes                                                      */
/* PUPRPOSE: To implement various I/O funcitons for general use.             */
/* METHOD DESCRIPTIONS:                                                      */
/*     void fatal(char *fmt, ...);                                           */
/*         Prints an error message to STDERR and exits the program.          */
/*                                                                           */
/*     char *readFILE(FILE *fp);                                             */
/*         Reads a string from a file and returns it.                        */
/*                                                                           */
/*     int isSpace(char c);                                                  */
/*         Returns whether the given character is whitespace                 */
/*         (' ', '\n', '\t')                                                 */
/*                                                                           */
/*     int isUpper(char c);                                                  */
/*         Returns whether the given character is an upper case letter.      */
/*                                                                           */
/*     int isLower(char c);                                                  */
/*         Returns whether the given character is a lower case letter.       */
/*                                                                           */
/*     int isDigit(char c);                                                  */
/*         Returns whether the given character is a numerical digit (0 - 9). */
/*                                                                           */
/*     int isOperator(char c);                                               */
/*         Returns whether the given character is a mathematical operator:   */
/*         (^, *, /, +, -, =)                                                */
/*                                                                           */
/*     int isPunc(char c);                                                   */
/*         Return whether the given character is a punctuation mark.         */
/*                                                                           */
/*     char toLower(char c);                                                 */
/*         Covnerts the given character to lower case if it is an upper case */
/*         character.                                                        */
/*                                                                           */
/*     char toUpper(char c);                                                 */
/*         Converts the given character to upper case if it a lower case     */
/*         chracter.                                                         */
/*                                                                           */
/*****************************************************************************/

/*** CONSTANTS ***/
#define TRUE 1
#define FALSE 0

/*** STRUCTS ***/
//none

/*** PRIVATE FUNCTION DECLARATIONS ***/
//none

/*** PUBLIC FUNCTION DEFINITIONS ***/
void fatal(char *fmt , ...){

    va_list listPtr;
    va_start(listPtr, fmt);
    vfprintf(stderr, fmt, listPtr);
    va_end(listPtr);

    exit(1);

    }

char *readFILE(FILE *fp){

    if(stringPending(fp)) return readString(fp);
    else return readToken(fp);

    }

int isUpper(char c){

    if(c >= 'A' && c <= 'Z') return TRUE;
    else return FALSE;

    }

int isLower(char c){

    if(c >= 'a' && c <= 'z') return TRUE;
    else return FALSE;

    }

int isSpace(char c){

    if(c == ' ' || c == '\t' || c == '\n') return TRUE;
    else return FALSE;

    }

char toLower(char c){

    if(isUpper(c)) return c + 32;
    else return c;

    }

char toUpper(char c){

    if(isLower(c)) return c - 32;
    else return c;

    }

int isDigit(char c){

    if(c >= '0' && c <= '9') return TRUE;
    else return FALSE;

    }

int isOperator(char c){

    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' ||
       c == '<' || c == '>' || c == '=' || c == '!') return TRUE;
    else return FALSE;

    }

int isPunc(char c){

    if(isSpace(c) == FALSE && isDigit(c) == FALSE && isUpper(c) == FALSE &&
       isLower(c) == FALSE) return TRUE;
    else return FALSE;

    }

/*** PRIVATE FUNCTION DEFINITIONS ***/
//none
