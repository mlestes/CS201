/*****************************************************************************/
// type.h by Murray Estes
// Header file for a custom type class.
// Begin Date: 20190117
// Complete Date: 
/*****************************************************************************/

#include <stdlib.h>

#ifndef __TYPE_H__
#define __TYPE_H__

typedef struct Type_type type_t;

#define INTEGER "INTEGER"
#define REAL "REAL"
#define STRING "STRING"

type_t *newType(void *);
void *getTypeValue(type_t *);
char *getTypeCast(type_t *);

#endif
