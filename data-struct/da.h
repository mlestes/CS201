#ifndef __DARRAY__H
#define __DARRAY__H

/*****************************************************************************/
/* darray.h BY Murray Estes                                                  */
/* PURPOSE: To hold public functions for a generic dynamic array.            */
/*****************************************************************************/

#include <stdio.h>

typedef struct dynarray DA;

extern DA *newDA(void (*d)(FILE *, void *));
extern void insertDA(DA *item, void *value);
extern void *removeDA(DA *item);
extern void unionDA(DA *reciever, DA *donor);
extern void *getDA(DA *item, int index);
extern void *setDA(DA *item, int index, void *value);
extern void **extractDA(DA *item);
extern int sizeDA(DA *item);
extern void visualizeDA(FILE *fp, DA *item);
extern void displayDA(FILE *fp, DA *item);

#endif

