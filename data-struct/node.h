#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>

/*****************************************************************************/
/* node.h BY Murray Estes                                                    */
/* PURPOSE: To generate a header file for a generic node structure.          */
/*****************************************************************************/

typedef struct NODE node;

extern node *newNode(void *);
extern void *getNode(node *);
extern void *setNode(node *, void *);
extern node *getNextNode(node *);
extern node *getPrevNode(node *);
extern node *getLeftNode(node *);
extern node *getRightNode(node *);
extern node *getHeadNode(node *);
extern node *getTailNode(node *);
extern node *getParentNode(node *);
extern node *setNextNode(node *, node *);
extern node *setPrevNode(node *, node *);
extern node *setLeftNode(node *, node *);
extern node *setRightNode(node *, node *);
extern node *setHeadNode(node *, node *);
extern node *setTailNode(node *, node *);
extern node *setParentNode(node *, node *);

#endif
