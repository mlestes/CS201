#include <assert.h>
#include <stdlib.h>
#include "queue.h"
#include "cda.h"

/*****************************************************************************/
/* queue.c BY Murray Estes                                                   */
/* PURPOSE: To implement a generic queue class based upon a circular         */
/*          dynamic array.                                                   */
/* FUNCTION DESCRIPTIONS:                                                    */
/*      queue *newQueue(void (*d)(FILE *, void *));                          */
/*           Creates a new queue object. The parameter is a function that is */
/*           able to display the values stored in the queue.                 */
/*                                                                           */
/*      void enqueue(queue *item, void *value);                              */
/*           Adds an item to the back of the queue.                          */
/*                                                                           */
/*      void *dequeue(queue *item);                                          */
/*           Removes and returns the item at the front of the queue.         */
/*                                                                           */
/*      void *peekQueue(queue *item);                                        */
/*           Returns the item at the front of the queue without removing it. */
/*                                                                           */
/*      int sizeQueue(queue *item);                                          */
/*           Returns the number of items in the queue.                       */
/*                                                                           */
/*      void displayQueue(FILE *fp, queue *item);                            */
/*           Prints the items stored in the queue in the order they were     */
/*           given. Example: <1,2,3,4>                                       */
/*                                                                           */
/*      void visualizeQueue(FILE *fp, queue *item);                          */
/*           Calls the display method of the data structure within the queue.*/
/*                                                                           */
/*****************************************************************************/

struct Queue{
	
    CDA *array;
    int front;
    void (*display)(FILE *, void *);

    };
	
// PRIVATE FUNCTION SIGNATURES //
//none

// PUBLIC FUNCTIONS //
QUEUE *newQUEUE(void (*d)(FILE *, void *)){

    QUEUE *q = malloc(sizeof(QUEUE));
    assert(q != 0);
    q->array = newCDA(d);
    q->display = d;

    return q;

    }

void enqueue(QUEUE *item, void *value){

    insertCDAback(item->array, value);

    }

void *dequeue(QUEUE *item){

    assert(sizeCDA(item->array) > 0);
    void *thing = removeCDAfront(item->array);

    return thing;

    }

void *peekQUEUE(QUEUE *item){

    assert(sizeCDA(item->array) > 0);
    void *thing = getCDA(item->array, 0);

    return thing;

    }

int sizeQUEUE(QUEUE *item){
	
    return sizeCDA(item->array);
	
    }

void displayQUEUE(FILE *fp, QUEUE *item){

    int size = sizeCDA(item->array);
    fprintf(fp, "<");
    for(int i = 0; i < size; i++){
        void *t = getCDA(item->array, i);
        item->display(fp, t);
        if(i < size - 1) fprintf(fp, ",");
        }
    fprintf(fp, ">");

    }    

void visualizeQUEUE(FILE *fp, QUEUE *item){

    displayCDA(fp, item->array);

    }

// PRIVATE FUNCTIONS
//none

