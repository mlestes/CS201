#ifndef __RBT_H__
#define __RBT_H__

#include <stdio.h>

/*****************************************************************************/
/* rbt.h BY Murray Estes                                                     */
/* PURPOSE: To provide a header file for a red-black tree class.             */
/*****************************************************************************/

typedef struct rbt RBT; //why uppercase object name?

extern RBT *newRBT(void (*)(FILE *, void *), int (*)(void *, void *));
extern void insertRBT(RBT *, void *);
extern void *findRBTNode(RBT *, void *);
extern int findRBT(RBT *, void *);
extern void deleteRBT(RBT *, void *);
extern int sizeRBT(RBT *);
extern int wordsRBT(RBT *); //wordCountRBT() is a better name
extern void statisticsRBT(FILE *, RBT *);
extern void displayRBT(FILE *, RBT *);

#endif
