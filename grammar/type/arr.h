#ifndef __ARR_H__
#define __ARR_H__

#include <stdlib.h>

typedef struct Array_Type array_t;

array_t *new_array(void (*d)(FILE *, void *));
void *insert_array(array_t *arr, void *item);
void *get_array(array_t *arr, int pos);
void print_array(FILE *fp, array_t *arr);
int size_array(array_t *arr);

#endif