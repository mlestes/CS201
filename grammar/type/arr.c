/*****************************************************************************/
// arr.c by Murray Estes
// Implements a dynamic array for general use.
// Date Began: 20190216
// Date Complete:
/*****************************************************************************/
// Usage:
// new_array(void) - creates a new, empty array object.
//      array_t *arr = new_array();
// 
// void *insert_array(array_t *arr, void *item) - inserts an object into the 
//                                                array and returns the 
//                                                inserted value.
//      obj *item = insert_array(arr, item);
//
// void *get_array(array_t *arr, int pos) - returns the object at the 
//                                          designated position.
//      void *obj = get_array(arr, 1);
//
// void print_array(FILE *fp, array_t *arr) - prints the array object.
//      print_array(stdout, arr);
//
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "arr.h"

/*** STRUCTURE ***/
struct Array_Type{

    void **array;
    int size; //number of items in the array
    int cap; //maximum number of items the array can hold before growing
    void (*display)(FILE *, void *);

};

/*** PRIVATE FUNCTION DECLARATIONS ***/
void grow_array(array_t *);
void shrink_array(array_t *);

/*** PUBLIC FUNCTION DEFINITIONS ***/
array_t *new_array(void (*d)(FILE *, void *)){

    array_t *arr = malloc(sizeof(array_t));
    arr->array = malloc(sizeof(void *));
    arr->size = 0;
    arr->cap = 1;
    arr->display = d;

    return arr;

}

void *insert_array(array_t *arr, void *item){

    arr->array[arr->size++] = item;
    if(arr->size == arr->cap) grow_array(arr);
    return item;

}

void *get_array(array_t *arr, int pos){return arr->array[pos];}
void print_array(FILE *fp, array_t *arr){

    int i;
    for(i = 0; i < arr->size; i++) arr->display(fp, arr->array[i]);

}
/*** PRIVATE FUNCTION DEFINITIONS ***/
void grow_array(array_t *arr){

    arr->cap *= 2;
    arr->array = realloc(arr->array, sizeof(void *) * arr->cap);

}

void shrink_array(array_t *arr){

    arr->cap = arr->cap / 4;
    arr->array = realloc(arr->array, sizeof(void *) * arr->cap);

}