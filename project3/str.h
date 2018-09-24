#ifndef __STR_H__
#define __STR_H__

#include <stdio.h>

/*****************************************************************************/
/* str.h BY Murray Estes                                                     */
/* PURPOSE: To provide a header file for a custom string class.              */
/*                                                                           */
/*****************************************************************************/

typedef struct STRING string;

extern string *newString(char *);
extern char *getString(string *);
extern char *setString(string *, char *);
extern void printString(FILE *, void *);
extern int sizeString(string *);
extern int compareString(void *, void *);

#endif
