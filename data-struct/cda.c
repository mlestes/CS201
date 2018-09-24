#include <assert.h>
#include <stdlib.h>
#include "cda.h"

/*****************************************************************************/
/* cdarray.c BY Murray Estes                                                 */
/* PURPOSE: To implement a generic circular dynamic array.                   */
/* FUNCTION DESCRIPTIONS:                                                    */
/*      cdarray *newCDA(void (*d)(FILE *, void *));                          */
/*           Creates a new circular dynamic array. The parameter is a        */
/*           function that can display the type of value stored in the array.*/
/*                                                                           */
/*      void insertCDAFront(cdarray *item, void *value);                     */
/*           Inserts an item in front of the first item in the filled portion*/
/*           of the array. If the array is full, it's capacity is doubled.   */
/*                                                                           */
/*      void insertCDABack(cdarray *item, void *value);                      */
/*           Inserts an item behind the last item in the filled portion of   */
/*           the array. If the array is full, it's size is doubled.          */
/*                                                                           */
/*      void *removeCDAFront(cdarray *item);                                 */
/*           Removes the first item in the filled region of the array. If the*/
/*           array becomes filled at less than 25% capacity, it shrinks by   */
/*           half.                                                           */
/*                                                                           */
/*      void *removeCDABack(cdarray *item);                                  */
/*           Removes the last item in the filled region of the array. If the */
/*           array becomes filled at less than 25% capacity, it shrinks by   */
/*           half.                                                           */
/*                                                                           */
/*      void unionCDA(cdarray *reciever, cdarray *donor);                    */
/*           Transfers the contents of the donor array to the recieving      */
/*           array.                                                          */
/*                                                                           */
/*      void *getCDA(cdarray *item, int index);                              */
/*           Returns the value at the given index.                           */
/*                                                                           */
/*      void *setCDA(cdarray *item, int index, void *value);                 */
/*           Updates the value at the given index. If index == size, the     */
/*           value is inserted via insertCDArrayBack. If index == -1, the    */
/*           value is inserted via insertCDArrayFront. The fuction returns   */
/*           the replaced value if one is replaced, null otherwise.          */
/*                                                                           */
/*      void **extractCDA(cdarray *item);                                    */
/*           Returns the C-array withing the object. The array is fit to size*/
/*           prior to being returned. The object then recieves a new, empty  */
/*           array.                                                          */
/*                                                                           */
/*      int sizeCDA(cdarray *item);                                          */
/*           Returns the size of the array.                                  */
/*                                                                           */
/*      void visualizeCDA(FILE *fp, cdarray *item);                          */
/*           Prints the filled portion of the array, surrounded by brackets. */
/*           Prints the remaining number of empty spaces in a seperate set of*/
/*           Brackets. Example: (1,2,3)(1)                                   */
/*                                                                           */
/*      void displayCDA(FILE *fp, cdarray *item);                            */
/*           Prints the contents of the array.                               */
/*                                                                           */
/*****************************************************************************/

struct CDArray{

    void **array;
    int size;
    int capacity;
    int head;
    int tail;
    void (*display)(FILE *, void *);

    };
	
// PRIVATE FUNCTION SIGNATURES //
static void **newArray(int);
static void growArray(CDA *);
static void shrinkArray(CDA *);

// PUBLIC FUNCTIONS //
CDA *newCDA(void (*d)(FILE *, void *)){

    CDA *cda = malloc(sizeof(CDA));
    assert(cda != 0);
    cda->array = newArray(1);
    cda->capacity = 1;
    cda->size = 0;
    cda->head = 0;
    cda->tail = 0;
    cda->display = d;
	
    return cda;

    }

void insertCDAfront(CDA *item, void *value){

    if(item->size == item->capacity){
        growArray(item);
        item->head = 0;
        item->tail = item->size;
        }
    item->head--;
    if(item->head < 0) item->head = item->capacity - 1;
    item->array[item->head] = value;
    item->size++;

    }

void insertCDAback(CDA *item, void *value){

    if(item->size == item->capacity){
        growArray(item);
        item->head = 0;
        item->tail = item->size;
        }
    item->array[item->tail] = value;
    item->tail++;
    if(item->tail == item->capacity) item->tail = 0;
    item->size++;

    }

void *removeCDAfront(CDA *item){

    assert(item->size > 0);
    void *temp = item->array[item->head];
    item->array[item->head] = NULL;
    item->head++;
    if(item->head == item->capacity) item->head = 0;
    item->size--;
    if(item->size < item->capacity / 4){
        shrinkArray(item);
        item->head = 0;
        item->tail = item->size;
        }

    return temp;

    }

void *removeCDAback(CDA *item){

    assert(item->size > 0);
    item->tail--;
    if(item->tail == 0) item->tail = item->capacity - 1;
    void *temp = item->array[item->tail];
    item->array[item->tail] = NULL;
    item->size--;
    if(item->size < item->capacity / 4){
        shrinkArray(item);
        item->head = 0;
        item->tail = item->size;
        }

    return temp;

    }

void unionCDA(CDA *reciever, CDA *donor){

    for(int i = 0; i < donor->size; i++){
        int index = donor->head + i;
        if(index >= donor->capacity) index = index - donor->capacity;
        insertCDAback(reciever, donor->array[index]);
        }
    donor->array = newArray(1);
    donor->head = 0; donor->size = 0; donor->capacity = 1; donor->tail = 0;
    
    }

void *getCDA(CDA *item, int index){

    assert(index >= 0 && index < item->size);
    int i = item->head + index;
    if(i >= item->capacity) i = i - item->capacity;

    return item->array[i];

    }

void *setCDA(CDA *item, int index, void *value){

    assert(index >= -1 && index <= item->size);
    if(index == item->size){
        insertCDAback(item, value);
        return 0;
        }

    else{
        int i = item->head + index;
        if(i >= item->capacity) i = i - item->capacity;
        if(i == -1) i = item->capacity - 1;
        void *temp = item->array[i];
        item->array[i] = value;
        if(temp) return temp;
        else return 0;
        }

    }

void **extractCDA(CDA *item){

    int size = item->size;
    void **temp = newArray(size);
    int index;
    for(int i = 0; i < size; i++){
        index = i + item->head;
        if(index > item->capacity) index = index - item->capacity;
        temp[i] = item->array[index];
        }
    item->array = newArray(1);
    item->head = 0; item->size = 0; item->capacity = 1; item->tail = 0;
	
    return temp;

    }

int sizeCDA(CDA *item){

    return item->size;

    }

void visualizeCDA(FILE *fp, CDA *item){

    displayCDA(fp, item);
    fprintf(fp, "(%d)", item->capacity - item->size);

    }

void displayCDA(FILE *fp, CDA *item){

    int index = 0;
    fprintf(fp, "(");
    for(int i = 0; i < item->size; i++){
            index = i + item->head;
            if(index >= item->capacity) index = index - item->capacity;
            item->display(stdout, item->array[index]);
            if(i < item->size - 1) fprintf(fp, ",");
        }
    fprintf(fp, ")");
	
    }

// PRIVATE FUNCTIONS //
//Creates a new array of type void *
void **newArray(int size){
	
    void **array = malloc(sizeof(void *) * size);
    assert(array != 0);
	
    return array;
	
    }

//Doubles the size of the object's array
void growArray(CDA *array){

    void **temp = newArray(2 * array->capacity);
    int index = 0;
    for(int i = 0; i <= array->size; i++){
        index = i + array->head;
        if(index >= array->capacity) index = index - array->capacity;
        temp[i] = array->array[index];
        }
    array->array = temp;
    array->capacity = 2 * array->capacity;

    }

//Shrinks the size of the object's array by half
void shrinkArray(CDA *array){

    void **temp = newArray(array->capacity / 2);
    int index = 0;
    for(int i = 0; i <= array->size; i++){
        index = i + array->head;
        if(index >= array->capacity) index = index - array->capacity;
        temp[i] = array->array[index];
        }
    array->array = temp;
    array->capacity = array->capacity / 2;

    }

