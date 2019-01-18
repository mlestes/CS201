/*****************************************************************************/
// type.h by Murray Estes
// Header file for a custom type class.
// Begin Date: 20190117
// Complete Date: 
/*****************************************************************************/

#include <stdlib.h>

#ifndef __TYPE_H__
#define __TYPE_H__

typedef struct Type type;

#define INTEGER "INTEGER"
#define REAL "REAL"
#define STRING "STRING"

type *newType(void *);
void *getTypeValue(type *);
char *getTypeType(type *);

#endif
