#ifndef STACK_H
#define STACK_H

#include <stdio.h>

/*****************************************************************************/
/* stack.h BY Murray Estes                                                   */
/* PURPOSE: To provide function signatures for a stack object based upon a   */
/*          generic circular dynamic array.                                  */
/*****************************************************************************/

typedef struct stack STACK;

extern STACK *newSTACK(void (*d)(FILE *, void *));
extern void push(STACK *item, void *value);
extern void *pop(STACK *item);
extern void *peekSTACK(STACK *item);
extern int sizeSTACK(STACK *item);
extern void displaySTACK(FILE *fp, STACK *item);
extern void visualizeSTACK(FILE *fp, STACK *item);

#endif
