#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "gt.h"

/*****************************************************************************/
/* gt.c BY Murray Estes                                                      */
/* PURPOSE: To implement a green tree class for use in storing words read in */
/*          from a corpus.                                                   */
/* METHOD DESCRIPTIONS:                                                      */
/*     GT *newGT(void (*d)(FILE *, void *), int (*c)(void *, void *));       */
/*         Creates a new green tree object. Parameters are a function that   */
/*         can display generic values and a function that can compare generic*/
/*         values.                                                           */
/*                                                                           */
/*     void insertGT(GT *g, void *value);                                    */
/*         Inserts the given value into the given tree.                      */
/*                                                                           */
/*     int findGT(GT *g, void *value);                                       */
/*         Returns whether the given value is in the given tree.             */
/*                                                                           */
/*     void deleteGT(GT *g, void *value);                                    */
/*         Deletes the given value from the tree.                            */
/*                                                                           */
/*     int sizeGT(GT *g);                                                    */
/*         Returns the number of nodes in the given tree.                    */
/*                                                                           */
/*     int wordsGT(GT *g);                                                   */
/*         Returns the number of words inserted into the tree, including     */
/*         duplicates.                                                       */
/*                                                                           */
/*     void statisticsGT(FILE *fp, GT *g);                                   */
/*         Displays a report of various statistics regarding the given tree. */
/*                                                                           */
/*     void displayGT(FILE *fp, GT *g);                                      */
/*         Displays the tree and some characteristics of each node.          */
/*                                                                           */
/*****************************************************************************/

/*** CONSTANTS ***/
#define TRUE 1
#define FALSE 0
#define MIN 1
#define MAX 2

/*** STRUCTS ***/
typedef struct gtNODE{

    void *store;
    int freq;
    void (*display)(FILE *, void *);
    int (*comparator)(void *, void *);

    }gtnode;

struct gt{

    BST *tree;
    int size;
    void (*display)(FILE *, void *);
    int (*comparator)(void *, void *);

    };

/*** PRIVATE FUNCTION DECLARATIONS ***/
static gtnode *newNode
    (void *, void (*)(FILE *, void *), int (*)(void *, void *));
static void displayGTNode(FILE *, void *);
static int compareGTNode(void *, void *);
static void incSize(GT *);
static void decSize(GT *);

/*** PUBLIC FUNCTION DEFINITIONS ***/
GT *newGT(void (*d)(FILE *, void *), int (*c)(void *, void *)){

    GT *g = malloc(sizeof(GT));
    assert(g != 0);
    g->tree = newBST(displayGTNode, compareGTNode, 0);
    g->display = d;
    g->comparator = c;

    return g;

    }

void insertGT(GT *g, void *value){

    gtnode *gnode = newNode(value, g->display, g->comparator);
    BSTNODE *node = findBST(g->tree, gnode);
    if(node == 0) node = insertBST(g->tree, gnode);
    gnode = getBSTNODE(node);
    gnode->freq++;
    incSize(g);

    }

int findGT(GT *g, void *value){

    int freq = 0;
    gtnode *test = newNode(value, g->display, g->comparator);
    BSTNODE *bnode = findBST(g->tree, test);
    if(bnode){
        gtnode *gnode = getBSTNODE(bnode);
        freq = gnode->freq;
        }

    return freq;

    }

void deleteGT(GT *g, void *value){

    gtnode *test = newNode(value, g->display, g->comparator);
    BSTNODE *bnode = findBST(g->tree, test);
    if(bnode){
        gtnode *gnode = getBSTNODE(bnode);
        gnode->freq--;
        if(gnode->freq <= 0) deleteBST(g->tree, test);
        decSize(g);
        }
    else{
        fprintf(stdout, "Value ");
        g->display(stdout, value);
        fprintf(stdout, " not found.\n");
        }

    }

int sizeGT(GT *g){return sizeBST(g->tree);}
int wordsGT(GT *g){return g->size;}
void statisticsGT(FILE *fp, GT *g){

    int words = wordsGT(g);
    fprintf(fp, "Words/Phrases: %d\n", words);
    statisticsBST(fp, g->tree);

    }

void displayGT(FILE *fp, GT *g){

    if(sizeGT(g) == 0) fprintf(fp, "EMPTY\n");
    else displayBST(fp, g->tree);

    }

/*** PRIVATE FUNCTION DEFINITIONS ***/
gtnode *newNode(void *val, void (*d)(FILE *, void *), int (*c)(void *, void *)){

    gtnode *node = malloc(sizeof(gtnode));
    assert(node != 0);
    node->store = val;
    node->freq = 0;
    node->display = d;
    node->comparator = c;

    return node;

    }

void displayGTNode(FILE *fp, void *v){

    gtnode *node = (gtnode *) v;
    node->display(fp, node->store);
    if(node->freq > 1) fprintf(fp, "-%d", node->freq);

    }

int compareGTNode(void *a, void *b){

    gtnode *alpha = (gtnode *) a;
    gtnode *beta = (gtnode *) b;
    return alpha->comparator(alpha->store, beta->store);

    }

void incSize(GT *tree){tree->size += 1;}
void decSize(GT *tree){tree->size -= 1;}
