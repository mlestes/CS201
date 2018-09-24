#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include "queue.h"

/*****************************************************************************/
/* bst.c BY Murray Estes                                                     */
/* PURPOSE: To implement a generic binary search tree.                       */
/* METHOD DESCRIPTIONS:                                                      */
/*     bst *newBST(void (*)(FILE *, void *, void), int (*)(void *, void *)); */
/*         Creates a new object. Parameters are a display function and a     */
/*         comparator.                                                       */
/*                                                                           */
/*     void insertBST(bst *, void *, void *                                  */
/*         Inserts a new item into the tree object.                          */
/*                                                                           */
/*     int findBST(bst *, void *);                                           */
/*         Returns whether or not an item is in the tree.                    */
/*                                                                           */
/*****************************************************************************/

/*** CONSTANTS ***/
#define MIN 1
#define MAX 2
#define TRUE 1
#define FALSE 0
#define EQUAL 0

/*** STRUCTURES ***/
struct BSTNode{

    void * store;
    BSTNODE *left;
    BSTNODE *right;
    BSTNODE *parent;

    };

struct bst{
	
    BSTNODE *root;
    int size;
    void (*display)(FILE *, void *);
    int (*compare)(void *, void *);
    void (*swapper)(BSTNODE *, BSTNODE *);

    };

/*** PRIVATE FUNCTION SIGNATURES ***/
static BSTNODE *newNode(void *);
static int findHeight(BSTNODE *, int);
static int isleaf(BSTNODE *);
static int isroot(BSTNODE *);
static void swapNodes(BSTNODE *, BSTNODE *);
static BSTNODE *getPredecessor(BSTNODE *);
static BSTNODE *getSuccessor(BSTNODE *);
static BSTNODE *insert(BST *, BSTNODE *, void *);
static void incSize(BST *);
static void decSize(BST *);
static int min(int, int);
static int max(int, int);

/*** PUBLIC METHODS ***/
//node
void *getBSTNODE(BSTNODE *n){return n->store;}
void setBSTNODE(BSTNODE *n, void *val){n->store = val;}
BSTNODE *getBSTNODEleft(BSTNODE *n){return n->left;}
void setBSTNODEleft(BSTNODE *n, BSTNODE *l){n->left = l;}
BSTNODE *getBSTNODEright(BSTNODE *n){return n->right;}
void setBSTNODEright(BSTNODE *n, BSTNODE *r){n->right = r;}
BSTNODE *getBSTNODEparent(BSTNODE *n){return n->parent;}
void setBSTNODEparent(BSTNODE *n, BSTNODE *p){n->parent = p;}
//tree
BST *newBST(
    void (*d)(FILE *, void *), 
    int (*c)(void *, void *), 
    void (*s)(BSTNODE *, BSTNODE *)){
	
    BST *b = malloc(sizeof(BST));
    assert(b != 0);
    b->root = 0;
    b->size = 0;
    b->display = d;
    b->compare = c;
    b->swapper = s;
	
    return b;
	
    }

void setBSTroot(BST *tree, BSTNODE *node){

    tree->root = node;
    if(node != 0)setBSTNODEparent(node, node);

    }

BSTNODE *getBSTroot(BST *tree){return tree->root;}
BSTNODE *insertBST(BST *tree, void *val){

    int inserted = FALSE;
    BSTNODE *node = getBSTroot(tree);
    if(node == 0){
        node = newNode(val);
        setBSTroot(tree, node);
        }
    else{
        while(inserted == FALSE){
            node = insert(tree, node, val);
            if(tree->compare(getBSTNODE(node), val) == EQUAL) inserted = TRUE;
            }
        }
    incSize(tree);
    
    return node;

    }

BSTNODE *findBST(BST *tree, void *val){
    
    BSTNODE *found = 0;
    BSTNODE *temp = getBSTroot(tree);
    while(temp){
        void *test = getBSTNODE(temp);
        if(tree->compare(test, val) == 0){
            found = temp;
            break;
            }
        else if(tree->compare(test, val) < 0) temp = getBSTNODEright(temp);
        else if(tree->compare(test, val) > 0) temp = getBSTNODEleft(temp);
        }

    return found;
	
    }

BSTNODE *deleteBST(BST *tree, void *val){

    BSTNODE *node = findBST(tree, val);
    if(node == 0){
        fprintf(stdout, "Value ");
        tree->display(stdout, val);
        fprintf(stdout, " not found.\n");
        }
    else{
        if(isleaf(node) == FALSE) node = swapToLeafBST(tree, node);
        pruneLeafBST(tree, node);
        }

    return node;

    }

BSTNODE *swapToLeafBST(BST *tree, BSTNODE *node){

    BSTNODE *swapnode = getPredecessor(node);
    if(swapnode == 0) swapnode = getSuccessor(node);
    if(swapnode == 0) swapnode = node;
    if(tree->swapper != 0) tree->swapper(node, swapnode);
    else swapNodes(node, swapnode);
    if(isleaf(swapnode) == TRUE) return swapnode;
    else return swapToLeafBST(tree, swapnode);

    }

void pruneLeafBST(BST *tree, BSTNODE *node){

    if(isroot(node) == TRUE) setBSTroot(tree, 0);
    BSTNODE *p = getBSTNODEparent(node);
    if(getBSTNODEleft(p) == node) setBSTNODEleft(p, 0);
    else if(getBSTNODEright(p) == node) setBSTNODEright(p, 0);
    setBSTNODEparent(node, 0);
    decSize(tree);

    }
int sizeBST(BST *tree){return tree->size;}
void statisticsBST(FILE *fp, BST *tree){

    int size = sizeBST(tree);
    int min = findHeight(tree->root, MIN);
    int max = findHeight(tree->root, MAX);
    fprintf(fp, "Nodes: %d\nMinimum depth: %d\nMaximum depth: %d\n",
            size, min, max);

    }

void displayBST(FILE *fp, BST *tree){

    if(sizeBST(tree) == 0) fprintf(fp, "EMPTY\n");
    else{
        QUEUE *q = newQUEUE(tree->display);
        BSTNODE *node = getBSTroot(tree);
        int h = 0; int i = 0; int l = 1; int d = 0;
        enqueue(q, node);
        while(sizeQUEUE(q) > 0){
            if(d == 0) fprintf(fp, "%d: ", h);
            else fprintf(fp, " ");
            node = dequeue(q); d++;
            if(node->left != 0){
                enqueue(q, node->left);
                i++;
                }
            if(node->right != 0){
                enqueue(q, node->right);
                i++;
                }
            if(isleaf(node)) fprintf(fp, "=");
            tree->display(fp, node->store);
            fprintf(fp, "(");
            tree->display(fp, node->parent->store);
            fprintf(fp, ")");
            if(node == node->parent->left) fprintf(fp, "-l");
            else if(node == node->parent->right) fprintf(fp, "-r");
            else fprintf(fp, "-");
            if(d == l){
                h++;
                l = i;
                i = 0;
                d = 0;
                fprintf(fp, "\n");
                }
            }
        }

    }

/*** PRIVATE FUNCTIONS ***/
BSTNODE *newNode(void *val){

    BSTNODE *node = malloc(sizeof(BSTNODE));
    assert(node != 0);
    node->store = val;
    node->left = 0;
    node->right = 0;
    node->parent = node;

    return node;

    }

int findHeight(BSTNODE *node, int flag){

    int l = 0; int r = 0;
    BSTNODE *left; BSTNODE *right;
    if(node != 0){
        left = getBSTNODEleft(node);
        right = getBSTNODEright(node);
        l = findHeight(left, flag);
        r = findHeight(right, flag);
        }
    if(node != 0 && flag == MIN) return min(l, r) + 1;
    else if(node != 0 && flag == MAX) return max(l, r) + 1;
    else return 0;

    }

int isleaf(BSTNODE *node){

    if(node->left == 0 && node->right == 0) return TRUE;
    else return FALSE;

    }

int isroot(BSTNODE *node){

    if(node->parent == node) return TRUE;
    else return FALSE;

    }

void swapNodes(BSTNODE *a, BSTNODE *b){

    void *va = getBSTNODE(a);
    void *vb = getBSTNODE(b);
    void *temp = va;
    setBSTNODE(a, vb);
    setBSTNODE(b, temp);

    }

BSTNODE *getPredecessor(BSTNODE *node){

    BSTNODE *pre = node->left;
    if(pre == 0) return 0;
    else{
        while(pre->right != 0) pre = pre->right;
        return pre;
        }

    }

BSTNODE *getSuccessor(BSTNODE *node){

    BSTNODE *suc = node->right;
    if(suc == 0) return 0;
    else{
        while(suc->left != 0) suc = suc->left;
        return suc;
        }

    }

BSTNODE *insert(BST *tree, BSTNODE *node, void *value){

    if(tree->compare(getBSTNODE(node), value) < 0){
        if(getBSTNODEright(node) == 0){
            setBSTNODEright(node, newNode(value));
            setBSTNODEparent(getBSTNODEright(node), node);
            }
        return getBSTNODEright(node);
        }
    else if(tree->compare(getBSTNODE(node), value) > 0){
        if(getBSTNODEleft(node) == 0){
            setBSTNODEleft(node, newNode(value));
            setBSTNODEparent(getBSTNODEleft(node), node);
            }
        return getBSTNODEleft(node);
        }

    else return node;

    }

void incSize(BST *tree){tree->size += 1;}
void decSize(BST *tree){tree->size -= 1;}
int min(int a, int b){

    if(a < b) return a;
    else return b;

    }

int max(int a, int b){

    if(a > b) return a;
    else return b;

    }
