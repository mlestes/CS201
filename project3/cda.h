#ifndef CDARRAY_H
#define CDARRAY_H

#include <stdio.h>

/*****************************************************************************/
/* cirdynarray.h BY Murray Estes                                             */
/* PURPOSE: To provide function signatures for a generic circular dynamic    */
/*          array.                                                           */
/*****************************************************************************/

typedef struct CDArray CDA;

extern CDA *newCDA(void (*d)(FILE *, void *));
extern void insertCDAfront(CDA *item, void *value);
extern void insertCDAback(CDA *item, void *value);
extern void *removeCDAfront(CDA *item);
extern void *removeCDAback(CDA *item);
extern void unionCDA(CDA *reciever, CDA *donor);
extern void *getCDA(CDA *item, int index);
extern void *setCDA(CDA *item, int index, void *value);
extern void **extractCDA(CDA *item);
extern int sizeCDA(CDA *item);
extern void visualizeCDA(FILE *, CDA *item);
extern void displayCDA(FILE *, CDA *item);

#endif

