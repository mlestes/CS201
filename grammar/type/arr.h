#ifndef __ARR_H__
#define __ARR_H__

#include <stdlib.h>

typedef struct Array_Type array_t;

array_t *new_array(void (*)(FILE *, void *));
void *insert_array(array_t *, void *);
void *get_array(array_t *, int);
void print_array(FILE *, array_t *);

#endif