#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>

/*****************************************************************************/
/* queue.h BY Murray Estes                                                   */
/* PURPOSE: To provide function signatures for a generic queue class based   */
/*          upon a generic dynamic array.                                    */
/*****************************************************************************/

typedef struct Queue QUEUE;

extern QUEUE *newQUEUE(void (*d)(FILE *, void *));
extern void enqueue(QUEUE *item, void *value);
extern void *dequeue(QUEUE *item);
extern void *peekQUEUE(QUEUE *item);
extern int sizeQUEUE(QUEUE *item);
extern void displayQUEUE(FILE *fp, QUEUE *item);
extern void visualizeQUEUE(FILE *fp, QUEUE *item);

#endif
