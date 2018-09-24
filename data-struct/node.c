#include <assert.h>
#include "node.h"

/*****************************************************************************/
/* node.c BY Murray Estes.                                                   */
/* PURPOSE: To implement a generic node structure that can be used in        */
/*          support of many larger data structures.                          */
/* METHOD DESCRIPTIONS:                                                      */
/*     node *newNode(void *val);                                             */
/*         Creates a new node object.                                        */
/*                                                                           */
/*     void *getNode(node *node);                                            */
/*         Returns the value of the given node.                              */
/*                                                                           */
/*     void *setNode(node *node, void *value);                               */
/*         Sets a new value into the given node. Returns the previous value. */
/*                                                                           */
/*     node *get____Node(node *node);                                        */
/*         Returns the node at the designated pointer.                       */
/*                                                                           */
/*     node *set____Node(node *node, node *____);                            */
/*         Sets a node to the designated pointer.                            */
/*                                                                           */
/*****************************************************************************/

struct NODE{

    void *value;
    node *next;
    node *prev;
    node *head;
    node *tail;
    node *left;
    node *right;
    node *parent;

    };

/*** PRIVATE FUNCTIONS ***/
//none

/*** PUBLIC METHODS ***/
node *newNode(void *val){

    node *n = malloc(sizeof(node));
    n->value = val;
    n->next = 0;
    n->prev = 0;
    n->head = 0;
    n->tail = 0;
    n->left = 0;
    n->right = 0;
    n->parent = 0;

    return n;

    }

void *setNode(node *node, void *val){

    assert(node != 0);
    void *thing = node->value;
    node->value = val;

    return thing;

    }

node *setNextNode(node *node, node *next){

    node *thing = node->next;
    node->next = next;

    return thing;

    }

node *setPrevNode(node *node, node *prev){

    node *thing = node->prev;
    node->prev = prev;

    return thing;

    }

node *setLeftNode(node *node, node *left){

    node *thing = node->left;
    node->left = left;

    return thing;

    }

node *setRightNode(node *node, node *right){

    node *thing = node->right;
    node->right = right;

    return thing;

    }

node *setHeadNode(node *node, node *head){

    node *thing = node->head;
    node->head = head;

    return thing;

    }

node *setTailNode(node *node, node *tail){

    node *thing = node->tail;
    node->tail = tail;

    return thing;

    }

node *setParentNode(node *node, node *parent){

    node *thing = node->parent;
    node->parent = parent;

    return thing;

    }

void *getNode(node *node){return node->value;}
node *getNextNode(node *node){return node->next;}
node *getPrevNode(node *node){return node->prev;}
node *getLeftNode(node *node){return node->left;}
node *getRightNode(node *node){return node->right;}
node *getHeadNode(node *node){return node->head;}
node *getTailNode(node *node){return node->tail;}
node *getParentNode(node *node){return node->parent;}

/*** PRIVATE FUNCTIONS ***/
//none
