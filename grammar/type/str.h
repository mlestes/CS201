#ifndef __STR_H__
#define __STR_H__

#include <stdio.h>

/*****************************************************************************/
/* str.h BY Murray Estes                                                     */
/* PURPOSE: To provide a header file for a custom string class.              */
/*                                                                           */
/*****************************************************************************/

typedef struct String_Type string_t;

extern string_t *newString(char *val);
extern char *getString(string_t *str);
extern char *setString(string_t *str, char *val);
extern void printString(FILE *fp, void *str);
extern int sizeString(string_t *str);
extern int compareString(void *a, void *b);

#endif
