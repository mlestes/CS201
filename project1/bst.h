#ifndef __BST_H__
#define __BST_H__

#include <stdio.h>

/*****************************************************************************/
/* bst.h BY Murray Estes                                                     */
/* PURPOSE: To provide a header file for a generic bst class.                */
/*****************************************************************************/

typedef struct bst BST;

extern BST *newBST(void (*)(FILE *, void *, void *), int (*)(void *, void *));
extern void insertBST(BST *, void *, void *);
extern void *findBST(BST *, void *);
extern int sizeBST(BST *);
extern void displayBST(FILE *, BST *);

#endif
