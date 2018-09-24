#ifndef __BST_H__
#define __BST_H__

#include <stdio.h>

/*****************************************************************************/
/* bst.h BY Murray Estes                                                     */
/* PURPOSE: To provide a header file for a generic bst class.                */
/*****************************************************************************/

/* Note to the instructor: Upper case type names are painful to type.
   Please consider using lower case names in the future. *smiley face* *wink**/

/*** BST NODE ***/
typedef struct BSTNode BSTNODE;

extern void *getBSTNODE(BSTNODE *);
extern void setBSTNODE(BSTNODE *, void *);
extern BSTNODE *getBSTNODEleft(BSTNODE *);
extern void setBSTNODEleft(BSTNODE *, BSTNODE *);
extern BSTNODE *getBSTNODEright(BSTNODE *);
extern void setBSTNODEright(BSTNODE *, BSTNODE *);
extern BSTNODE *getBSTNODEparent(BSTNODE *);
extern void setBSTNODEparent(BSTNODE *, BSTNODE *);

/*** Tree ***/
typedef struct bst BST;

extern BST *newBST(
    void (*)(FILE *, void *), 
    int (*)(void *, void *), 
    void (*)(BSTNODE *, BSTNODE *));
extern void setBSTroot(BST *, BSTNODE *);
extern BSTNODE *getBSTroot(BST *);
extern BSTNODE *insertBST(BST *, void *);
extern BSTNODE *findBST(BST *, void *);
extern BSTNODE *deleteBST(BST *, void *);
extern BSTNODE *swapToLeafBST(BST *, BSTNODE *);
extern void pruneLeafBST(BST *, BSTNODE *);
extern int sizeBST(BST *);
extern void statisticsBST(FILE *, BST *);
extern void displayBST(FILE *, BST *);

#endif
