#ifndef __CONVERT_H__
#define __CONVERT_H__

#include "queue.h"
#include "bst.h"

/*****************************************************************************/
/* convert.h BY Murray Estes                                                 */
/* PURPOSE: To create a header file for a function that converts postfix to  */
/*          infix notation.                                                  */
/*                                                                           */
/*****************************************************************************/

extern QUEUE *convert(QUEUE *, BST *);
extern double evaluate(QUEUE *);

#endif
