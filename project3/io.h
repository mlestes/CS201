#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>

extern void fatal(char *,...);
extern char *readFILE(FILE *);
extern int isSpace(char);
extern int isUpper(char);
extern int isLower(char);
extern int isDigit(char);
extern int isOperator(char);
extern int isPunc(char);
extern char toLower(char);
extern char toUpper(char);

#endif
