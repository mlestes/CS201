#ifndef __STR_H__
#define __STR_H__

#include <stdio.h>

/*****************************************************************************/
/* str.h BY Murray Estes                                                     */
/* PURPOSE: To provide a header file for a custom string class.              */
/*                                                                           */
/*****************************************************************************/

typedef struct String_Type string_t;

extern string_t *newString(char *);
extern char *getString(string_t *);
extern char *setString(string_t *, char *);
extern void printString(FILE *, void *);
extern int sizeString(string_t *);
extern int compareString(void *, void *);

#endif
