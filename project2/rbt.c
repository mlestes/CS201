#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rbt.h"
#include "bst.h"

/*****************************************************************************/
/* rbt.c BY Murray Estes                                                     */
/* PUPRPOSE: To implement a red-black tree for use in parsing text from a    */
/*           corpus.                                                         */
/* METHOD DESCRIPTIONS:                                                      */
/*     RBT *newRBT(void (*d)(FILE *, void *)(*c)(FILE *, void *));           */
/*          Creates a new red-black tree object. Parameters are a function   */
/*          that can display a generic value and a function that can compare */
/*          two generic values.                                              */
/*                                                                           */
/*     void insertRBT(RBT* r, void *value);                                  */
/*          Inserts the given value into the given tree.                     */
/*                                                                           */
/*     int findRBT(RBT *r, void *value):                                     */
/*          Returns whether the given value is in the given tree.            */
/*                                                                           */
/*     void deleteRBT(RBT *r, void *value);                                  */
/*          Removes the given value from the tree.                           */
/*                                                                           */
/*     int sizeRBT(RBT *r);                                                  */
/*          Returns the number of nodes in the tree.                         */
/*                                                                           */
/*     int wordsRBT(RBT *r);                                                 */
/*          Returns the number of words in the tree, including duplicates.   */
/*                                                                           */
/*     void statisticsRBT(FILE *fp, RBT *r);                                 */
/*          Displays various statistics about the words in the tree.         */
/*                                                                           */
/*     void displayRBT(FILE *fp, RBT *r);                                    */
/*          Displays each node and some information about each node.         */
/*                                                                           */
/*****************************************************************************/

/*** CONSTANTS ***/
#define TRUE 1
#define FALSE 0
#define RED 1
#define BLACK -1

/*** STRUCTS ***/
typedef struct RBTNode{

    void *store;
    int freq;
    int color;
    void (*display)(FILE *, void *);
    int (*comparator)(void *, void *);

    } rbtnode;

struct rbt{

    BST *tree;
    int size;
    void (*display)(FILE *, void *);
    int (*comparator)(void *, void *);

    };

/*** PRIVATE FUNCTION DECLARATIONS ***/
static void swap(BSTNODE *, BSTNODE *);
static void displayRBTNode(FILE *, void *);
static rbtnode *newNode
    (void *, void (*)(FILE *, void *), int (*)(void *, void *));
static void insertFix(RBT *, BSTNODE *);
static int isroot(BSTNODE *);
static int color(BSTNODE *);
static void setColor(BSTNODE *, int);
static BSTNODE *uncle(BSTNODE *);
static void rotate(RBT *, BSTNODE *);
static int islinear(BSTNODE *, BSTNODE *);
static int compare(RBT *, BSTNODE *, BSTNODE *);
static void deleteFix(RBT *, BSTNODE *);
static BSTNODE *sibling(BSTNODE *);
static BSTNODE *niece(BSTNODE *);
static BSTNODE *nephew(BSTNODE *);
static int compareRBTNode(void *, void *);
static void incSize(RBT *);
static void decSize(RBT *);

/*** PUBLIC FUNCTION DEFINITIONS ***/
RBT *newRBT(void (*d)(FILE *, void *), int (*c)(void *, void *)){

    RBT *r = malloc(sizeof(RBT));
    assert(r != 0);
    r->tree = newBST(displayRBTNode, compareRBTNode, swap);
    r->display = d;
    r->comparator = c;
    
    return r;

    }

void insertRBT(RBT *r, void *value){

    rbtnode *rnode = newNode(value, r->display, r->comparator);
    BSTNODE *node = findBST(r->tree, rnode);
    if(node == 0){
        node = insertBST(r->tree, rnode);
        insertFix(r, node);
        }
    rnode = getBSTNODE(node);
    rnode->freq++;
    incSize(r);

    }

int findRBT(RBT *r, void *value){

    int freq = 0;
    rbtnode *test = newNode(value, r->display, r->comparator);
    BSTNODE *bnode = findBST(r->tree, test);
    if(bnode){
        rbtnode *rnode = getBSTNODE(bnode);
        freq = rnode->freq;
        }

    return freq;

    }

void deleteRBT(RBT *r, void *value){

    rbtnode *test = newNode(value, r->display, r->comparator);
    BSTNODE *bnode = findBST(r->tree, test);
    if(bnode){
        rbtnode *rnode = getBSTNODE(bnode);
        rnode->freq--;
        if(rnode->freq <= 0){
            bnode = swapToLeafBST(r->tree, bnode);
            deleteFix(r, bnode);
            pruneLeafBST(r->tree, bnode);
            }
        decSize(r);
        }
    else{
        fprintf(stdout, "Value ");
        r->display(stdout, value);
        fprintf(stdout, " not found.\n");
        }

    }

int sizeRBT(RBT *r){return sizeBST(r->tree);}
int wordsRBT(RBT *r){return r->size;}
void statisticsRBT(FILE *fp, RBT *r){

    fprintf(fp, "Words/Phrases: %d\n", wordsRBT(r));
    statisticsBST(fp, r->tree);

    }

void displayRBT(FILE *fp, RBT *r){

    if(getBSTroot(r->tree) == 0) fprintf(fp, "EMPTY\n");
    else displayBST(fp, r->tree);

    }

/*** PRIVATE FUNCTION DEFINITIONS ***/
void swap(BSTNODE *a, BSTNODE *b){

    rbtnode *alpha = getBSTNODE(a);
    rbtnode *beta = getBSTNODE(b);
    void *val = alpha->store;
    alpha->store = beta->store;
    beta->store = val;
    int f = alpha->freq;
    alpha->freq = beta->freq;
    beta->freq = f;
    setBSTNODE(a, alpha);
    setBSTNODE(b, beta);

    }

rbtnode *newNode(void *val, void (*d)(FILE *, void *), int (*c)(void *, void *))
    {

    rbtnode *node = malloc(sizeof(rbtnode));
    assert(node != 0);
    node->store = val;
    node->freq = 0;
    node->color = RED;
    node->display = d;
    node->comparator = c;

    return node;

    }

void displayRBTNode(FILE *fp, void *v){

    rbtnode *node = (rbtnode *) v;
    node->display(fp, node->store);
    if(node->freq > 1) fprintf(fp, "-%d", node->freq);
    if(node->color == RED) fprintf(fp, "-R");
    if(node->color == BLACK) fprintf(fp, "-B");

    }

void insertFix(RBT *tree, BSTNODE *node){

    while(node){
        if(isroot(node) == TRUE) break;
        BSTNODE *parent = getBSTNODEparent(node);
        if(color(parent) == BLACK) break;
        if(color(uncle(node)) == RED){
            setColor(parent, BLACK);
            setColor(uncle(node), BLACK);
            setColor(getBSTNODEparent(parent), RED);
            node = getBSTNODEparent(parent);
            }
        else{ //uncle is black
            if(islinear(node, parent) == FALSE){
                rotate(tree, node);
                BSTNODE *temp = node;
                node = parent;
                parent = temp;
                }
            setColor(parent, BLACK);
            setColor(getBSTNODEparent(parent), RED);
            rotate(tree, parent);
            break;
            }
        }
    setColor(getBSTroot(tree->tree), BLACK);

    }

int color(BSTNODE *node){

    if(node == 0) return BLACK;
    else{

        rbtnode *rnode = getBSTNODE(node);
        return rnode->color;

        }

    }

int islinear(BSTNODE *node, BSTNODE *parent){

    BSTNODE *grand = getBSTNODEparent(parent);
    if(isroot(parent) == TRUE) return TRUE;
    else if((node == getBSTNODEleft(parent) && parent == getBSTNODEleft(grand)) 
        || 
        (node == getBSTNODEright(parent) && parent == getBSTNODEright(grand)))
        return TRUE;
    else return FALSE;

    }

int isroot(BSTNODE *node){

    if(getBSTNODEparent(node) == node) return TRUE;
    else return FALSE;

    }

void setColor(BSTNODE *node, int color){

    rbtnode *rnode = getBSTNODE(node);
    rnode->color = color;

    }

BSTNODE *uncle(BSTNODE *node){

    BSTNODE *parent = getBSTNODEparent(node);
    BSTNODE *grand = getBSTNODEparent(parent);
    if(parent == getBSTNODEleft(grand)) return getBSTNODEright(grand);
    else return getBSTNODEleft(grand);

    }

void rotate(RBT *tree, BSTNODE *node){

    BSTNODE *parent = getBSTNODEparent(node);
    BSTNODE *grand = getBSTNODEparent(parent);
    if(compare(tree, parent, node) > 0){
        BSTNODE *temp = getBSTNODEright(node);
        setBSTNODEright(node, parent);
        setBSTNODEleft(parent, temp);
        if(temp != 0) setBSTNODEparent(temp, parent);
        }
    else if(compare(tree, parent, node) < 0){
        BSTNODE *temp = getBSTNODEleft(node);
        setBSTNODEleft(node, parent);
        setBSTNODEright(parent, temp);
        if(temp != 0) setBSTNODEparent(temp, parent);
        }
    if(isroot(parent) == TRUE){
        setBSTroot(tree->tree, node);
        setBSTNODEparent(node, node);
        setBSTNODEparent(parent, node);
        }      
    else if(parent == getBSTNODEleft(grand)){
        setBSTNODEleft(grand, node);
        setBSTNODEparent(node, grand);
        setBSTNODEparent(parent, node);
        }
    else if(parent == getBSTNODEright(grand)){
        setBSTNODEright(grand, node);
        setBSTNODEparent(node, grand);
        setBSTNODEparent(parent, node);
        }

    }

int compare(RBT *tree, BSTNODE *a, BSTNODE *b){

    rbtnode *alpha = getBSTNODE(a);
    rbtnode *beta = getBSTNODE(b);
    return tree->comparator(alpha->store, beta->store);

    }

void deleteFix(RBT *tree, BSTNODE *node){

    while(node){
        if(isroot(node) == TRUE) break;
        if(color(node) == RED) break;
        BSTNODE *parent = getBSTNODEparent(node);
        if(color(sibling(node)) == RED){
            setColor(parent, RED);
            setColor(sibling(node), BLACK);
            rotate(tree, sibling(node));
            }
        else if(color(nephew(node)) == RED){
            setColor(sibling(node), color(parent));
            setColor(parent, BLACK);
            setColor(nephew(node), BLACK);
            rotate(tree, sibling(node));
            break;
            }
        else if(color(niece(node)) == RED){
            setColor(niece(node), BLACK);
            setColor(sibling(node), RED);
            rotate(tree, niece(node));
            }
        else{
            setColor(sibling(node), RED);
            node = parent;
            }
        }
    setColor(node, BLACK);

    }

BSTNODE *sibling(BSTNODE *node){

    BSTNODE *parent = getBSTNODEparent(node);
    if(node == getBSTNODEleft(parent)) return getBSTNODEright(parent);
    else return getBSTNODEleft(parent);

    }

BSTNODE *niece(BSTNODE *node){ //closest child of sibling

    BSTNODE *parent = getBSTNODEparent(node);
    if(node == getBSTNODEleft(parent)) return getBSTNODEleft(sibling(node));
    else return getBSTNODEright(sibling(node));

    }

BSTNODE *nephew(BSTNODE *node){ //furthest child of sibling

    BSTNODE *parent = getBSTNODEparent(node);
    if(node == getBSTNODEleft(parent)) return getBSTNODEright(sibling(node));
    else return getBSTNODEleft(sibling(node));

    }

int compareRBTNode(void *a, void *b){

    rbtnode *x = (rbtnode *) a;
    rbtnode *y = (rbtnode *) b;
    return x->comparator(x->store, y->store);

    }

void incSize(RBT *tree){tree->size += 1;}
void decSize(RBT *tree){tree->size -= 1;}
