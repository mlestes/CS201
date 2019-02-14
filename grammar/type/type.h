/*****************************************************************************/
// type.h by Murray Estes
// Header file for a custom type class.
// Begin Date: 20190117
// Complete Date: 
/*****************************************************************************/

#include <stdlib.h>

#ifndef __TYPE_H__
#define __TYPE_H__

#include "str.h"
#include "int.h"
#include "real.h"

typedef struct Type_type type_t;

#define INT 0
#define DBL 1
#define STR 2

type_t *newType(void *);
void *getTypeValue(type_t *);
int getTypeCast(type_t *);
void printType(FILE *, type_t *);

#endif
