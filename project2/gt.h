#ifndef __GT_H__
#define __GT_H__

#include <stdio.h>

/*****************************************************************************/
/* gt.h BY Murray Estes                                                      */
/* PURPOSE: To create a header file for a green tree class.                  */
/*****************************************************************************/

typedef struct gt GT; //why uppercase?

extern GT *newGT(void (*)(FILE *, void *), int (*)(void *, void *));
extern void insertGT(GT *, void *);
extern int findGT(GT *, void *); //should this be gt *?
extern void deleteGT(GT *, void *);
extern int sizeGT(GT *);
extern int wordsGT(GT *); //what do you do? wordCountGT() makes more sense
extern void statisticsGT(FILE *, GT *);
extern void displayGT(FILE *, GT *);

#endif
