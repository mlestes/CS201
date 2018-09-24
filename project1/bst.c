#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

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

/*** STRUCTURES ***/
struct bst{
	
    void *root;
    void *key;
    BST *left;
    BST *right;
    void (*display)(FILE *, void *, void *);
    int (*compare)(void *, void *);
	
    };

/*** PRIVATE FUNCTION SIGNATURES ***/
//none

/*** PUBLIC METHODS ***/
BST *newBST(void (*d)(FILE *, void *, void *), int (*c)(void *, void *)){
	
    BST *b = malloc(sizeof(BST));
    assert(b != 0);
    b->root = 0;
    b->key = 0;
    b->left = 0;
    b->right = 0;
    b->display = d;
    b->compare = c;
	
    return b;
	
    }

void insertBST(BST *tree, void *key, void *val){

    assert(tree != 0);
    if(tree->root == 0){
        tree->root = val;
        tree->key = key;
        }
    else if(tree->compare(tree->key, key) < 0){
    	if(tree->right == 0) tree->right = newBST(tree->display, tree->compare);
        insertBST(tree->right, key, val);
        }
    else if(tree->compare(tree->key, key) > 0){
        if(tree->left == 0) tree->left = newBST(tree->display, tree->compare);
        insertBST(tree->left, key, val);
        }
    else if(tree->compare(tree->key, key) == 0) tree->root = val;

    }

void *findBST(BST *tree, void *key){
    
    assert(tree != 0);
    void *found = 0;
    if(tree->root == 0) found = 0;
    else if(tree->compare(tree->key, key) == 0) found = tree->root;
    else if(tree->compare(tree->key, key) < 0){
        if(tree->right == 0) found = 0;
        else found = findBST(tree->right, key);
        }
    else if(tree->compare(tree->key, key) > 0){
        if(tree->left == 0) found = 0;
        else found = findBST(tree->left, key);
        }

    return found;
	
    }

int sizeBST(BST *tree){

    int count = 0;
    if(tree){
        int left = sizeBST(tree->left);
        int right = sizeBST(tree->right);
        if(tree->root) count = left + right + 1;
        }

    return count;

    }

void displayBST(FILE *fp, BST *tree){

    if(tree){
        fprintf(fp, "[");
        displayBST(fp, tree->left);
        if(tree->left) fprintf(fp, " ");
        if(tree->root) tree->display(fp, tree->key, tree->root);
        if(tree->right) fprintf(fp, " ");
        displayBST(fp, tree->right);
        fprintf(fp, "]");
        }

    }

/*** PRIVATE FUNCTIONS ***/
//none
