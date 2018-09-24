#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "da.h"

/*****************************************************************************/
/* darray.c BY Murray Estes                                                */
/* PURPOSE: To implement functionality for a generic dynamic array.          */
/* PUBLIC FUNCTION DESCRIPTIONS:                                             */
/*      darray *newDA(void (*d)(FILE *, void *));                            */
/*           Creates a new dynamic array. The parameter is a function that is*/
/*           capable of displaying the value stored in a given slot.         */
/*                                                                           */ 
/*      void insertDA(darray *item, void *value);                            */
/*           Inserts a value into the array. The value is inserted at the    */
/*           lowest-valued index available. The array doubles if it is full. */
/*                                                                           */
/*      void *removeDA(darray *item);                                        */
/*           Removes the item in the highest-valued index occupied. If the   */
/*           array becomes filled to less than 25% capacity, it shrinks by   */
/*           half.                                                           */
/*                                                                           */
/*      void unionDA(darray *reciever, darray *donor);                       */
/*           Transfers all items from the donor array and inserts them into  */
/*           the recieving array.                                            */
/*                                                                           */
/*      void *getDA(darray *item, int index);                                */
/*           Returns the value of the given index.                           */
/*                                                                           */
/*      void *setDA(darray *item, int index, void *value);                   */
/*           If the given index == size, then the value is inserted as via   */
/*           the insert function. Otherwise, the value of the given index is */
/*           returned if a value was replace, else a null pointer is passed  */
/*           if no value is replaced.                                        */
/*                                                                           */
/*      void **extractDA(darray *item);                                      */
/*           Returns the C-array within the object, fitted to size. The      */
/*           object then recieves a new, empty array.                        */
/*                                                                           */
/*      int sizeDA(darray *item);                                            */
/*           Returns the size of the given array.                            */
/*                                                                           */
/*      void visualizeDA(FILE *fp, darray *item);                            */
/*           Displays the filled portion of the array in brackets, then in a */
/*           seperate set of brackets, displays how many slots are unfilled. */
/*           Example output: [5,3,9,1][2]                                    */
/*                                                                           */
/*      void displayDA(FILE *fp, darray *item);                              */
/*           Displays the contents of the array.                             */
/*                                                                           */
/*****************************************************************************/

struct dynarray{
	
    void **array;
    int size;
    int capacity;
    void (*display)(FILE *, void *);
	
    };

/* PRIVATE FUNCTION SIGNATURES */
static void **newArray(int);

/* PUBLIC FUNCTIONS */
DA *newDA(void (*d)(FILE *, void *)){

    DA *da = malloc(sizeof(DA));
    assert(da != 0);
    da->array = newArray(1);
    da->capacity = 1;
    da->size = 0;
    da->display = d;

    return da;

    }

void insertDA(DA *item, void *value){

    int c = item->capacity;
    int s = item->size;
    if(c == s){
        void **temp = newArray(2 * c);
        int j = 0;
        for(int i = 0; i < s; i++){
            if(item->array[i]) temp[j++] = item->array[i];
            }
        item->array = temp;
        c = 2 * c;
        }

    item->array[s++] = value;
    item->size = s;
    item->capacity = c;

    }

void *removeDA(DA *item){

    assert(item->size > 0);
    int c = item->capacity;
    int s = item->size - 1;
    void *t = item->array[s];
    item->array[s] = NULL;
    item->size = s;
    if(s < c / 4 && c > 1){
        void **temp = newArray(c / 2);
        int j = 0;
        for(int i = 0; i < c; i++){
            if(item->array[i]) temp[j++] = item->array[i];
            }
        item->array = temp;
        item->capacity = c / 2;
        }
	
    return t;

    }

void unionDA(DA *reciever, DA *donor){

    for(int i = 0; i < donor->size; i++) 
        insertDA(reciever, donor->array[i]);
    donor->array = newArray(1);
    donor->size = 0;
    donor->capacity = 1;

    }

void *getDA(DA *item, int index){

    assert(0 <= index && index < item->size);
    return item->array[index];

    }

void *setDA(DA *item, int index, void *value){

    assert(0 <= index && index <= item->size);
    if(index == item->size){
        insertDA(item, value);
        return 0;
        }
    else{
        void *t = item->array[index];
        item->array[index] = value;
        if(!t) return 0;
        else return t;
        }
	

    }

void **extractDA(DA *item){

    int size = item->size;
    void **t = newArray(size);
    for(int i = 0; i < size; i++) t[i] = item->array[i];
    item->array = newArray(1);
    item->size = 0;
    item->capacity = 1;
	
    return t;

    }

int sizeDA(DA *item){

    return item->size;

    }

void visualizeDA(FILE *fp, DA *item){

    displayDA(fp, item);
    fprintf(fp,"[%d]", item->capacity - item->size);

    }

void displayDA(FILE *fp, DA *item){

    fprintf(fp,"[");
    for(int i = 0;i < item->size; i++){
        item->display(fp, item->array[i]);
        if(i < item->size - 1) fprintf(fp, ",");
        }
    fprintf(fp,"]");
	
    }

/* PRIVATE FUNCTIONS */
//Create a new array of type void *
void **newArray(int size){

    void **array = malloc(sizeof(void *) * size);
    assert(array != 0);

    return array;

    }
