#include <assert.h>
#include <stdlib.h>
#include "stack.h"
#include "da.h"

/*****************************************************************************/
/* stack.c BY Murray Estes                                                   */
/* PURPOSE: To implement a stack object using a generic dynamic array.       */
/* FUNCTION DESCRIPTIONS:                                                    */
/*      stack *newStack(void (*d)(FILE *, void *));                          */
/*           Creates a new stack object. The parameter is a function that is */
/*           able to display the values stored in the stack.                 */
/*                                                                           */
/*      void push(stack *item, void *value);                                 */
/*           Inserts a value to the top of the stack.                        */
/*                                                                           */
/*      void *pop(stack *item);                                              */
/*           Removes and returns the top item of the stack.                  */
/*                                                                           */
/*      void *peekStack(stack *item);                                        */
/*           Returns the top item of the stack without removing it.          */
/*                                                                           */
/*      int sizeStack(stack *item);                                          */
/*           Returns the number of items in the stack.                       */
/*                                                                           */
/*      void displayStack(FILE *fp, stack *item);                            */
/*           Prints the items stored in the stack in reverse order the items */
/*           will be popped. Example: |4,3,2,1|                              */
/*                                                                           */
/*      void visualizeStack(FILE *fp, stack *item);                          */
/*           Calls the display method of the array structure.                */
/*                                                                           */
/*****************************************************************************/

struct stack{
	
    DA *array;
    int top;
    void (*show)(FILE*, void *);
	
    };
	
// PRIVATE FUNCTION SIGNATURES //
//none

// PUBLIC FUNCTIONS //
STACK *newSTACK(void (*d)(FILE *, void *)){

    STACK *s = malloc(sizeof(STACK));
    assert(s != 0);
    s->array = newDA(d);
    s->show = d;
	
    return s;

    }

void push(STACK *item, void *value){

    insertDA(item->array, value);
	
    }

void *pop(STACK *item){

    assert(sizeDA(item->array) > 0);
    void *thing = removeDA(item->array); 
	
    return thing;

    }

void *peekSTACK(STACK *item){

    assert(sizeDA(item->array) > 0);
    void *thing = getDA(item->array, sizeDA(item->array) - 1);

    return thing;

    }

int sizeSTACK(STACK *item){
	
    return sizeDA(item->array);

    }

void displaySTACK(FILE *fp, STACK *item){

    fprintf(fp, "|");
    for(int i = 0; i < sizeDA(item->array); i++){
        int index = sizeDA(item->array) - 1 - i;
        void *t = getDA(item->array, index);
        item->show(fp, t);
        if(i < sizeDA(item->array) - 1) fprintf(fp, ",");
        }
    fprintf(fp, "|");

    }

void visualizeSTACK(FILE *fp, STACK *item){

    displayDA(fp, item->array);

    }

// PRIVATE FUNCTIONS
//none

