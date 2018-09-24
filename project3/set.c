#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//LOCAL INCLUDES
#include "set.h"
#include "da.h"

/*****************************************************************************/
/* template BY Murray Estes                                                  */
/* PUPRPOSE: template                                                        */
/* METHOD DESCRIPTIONS:                                                      */
/*     template                                                              */
/*                                                                           */
/*****************************************************************************/

/*** CONSTANTS ***/
#define TRUE 1
#define FALSE 0
#define DEFAULT -1

/*** STRUCTS ***/
struct set{

    DA *array;
    void (*display)(FILE *, void *);

    };

typedef struct setNODE{

    void *store;
    struct setNODE *rep;
    int parent;
    int index;
    int rank;

    }setnode;

/*** PRIVATE FUNCTION DECLARATIONS ***/
static setnode *newNode(void *);
static void *getNode(setnode *);
static setnode *getRep(setnode *);
static int getIndex(setnode *);
static void setIndex(setnode *, int);
static void setRep(setnode *, setnode *);
static int isrep(setnode *);
static int getRank(setnode *);
static void setRank(setnode *, int);
static int getParent(setnode *);
static void setParent(setnode *, int);
static setnode *getSET(SET *, int);

/*** PUBLIC FUNCTION DEFINITIONS ***/
SET *newSET(void (*d)(FILE *, void *)){

    SET *s = malloc(sizeof(SET));
    if(s == 0){
        fprintf(stdout, "Error: Failed to allocate memory...\n");
        exit(1);
        }
    s->array = newDA(d);
    s->display = d;

    return s;

    }

int makeSET(SET *set, void *val){

    setnode *node = newNode(val);
    insertDA(set->array, node);
    setIndex(node, sizeDA(set->array) - 1);
    setRep(node, node);
    return sizeDA(set->array) - 1;

    }

int findSET(SET *set, int index){

    setnode *node = getSET(set, index);
    setnode *rep = getRep(node);
    while(rep != getRep(rep)){
        setRep(node, rep);
        rep = getRep(rep);
        }

    return getIndex(rep);

    }

int unionSET(SET *set, int first, int second){

    if(findSET(set, first) == findSET(set, second)) return FALSE;
    else{
        setnode *ra = getSET(set, findSET(set, first));
        setnode *rb = getSET(set, findSET(set, second));
        if(getRank(ra) > getRank(rb)){
            setRep(rb, ra);
            setRank(ra, getRank(ra) + 1);
            if(getParent(rb) == DEFAULT) setParent(rb, getIndex(ra));
            }
        else if(getRank(ra) < getRank(rb)){
            setRep(ra, rb);
            setRank(rb, getRank(rb) + 1);
            if(getParent(ra) == DEFAULT) setParent(ra, getIndex(rb));
            }
        else{
            if(getIndex(ra) < getIndex(rb)){
                setRep(rb, ra);
                setRank(ra, getRank(ra) + 1);
                if(getParent(rb) == DEFAULT) setParent(rb, getIndex(ra));
                }
            else{
                setRep(ra, rb);
                setRank(rb, getRank(rb) + 1);
                if(getParent(ra) == DEFAULT) setParent(ra, getIndex(rb));
                }
            }
        return TRUE;
        }

    }

int countSET(SET *set){

    int count = 0;
    for(int i = 0; i < sizeDA(set->array); i++){
        setnode *node = getDA(set->array, i);
        if(isrep(node) == TRUE) count++;
        }

    return count;

    }

int displaySET(FILE *fp, SET *set){

    for(int i = 0; i < sizeDA(set->array); i++){
        fprintf(fp, "%d: ", i);
        setnode *node = getDA(set->array, i);
        set->display(fp, getNode(node));
        while(getParent(node) != DEFAULT){
            fprintf(fp, " ");
            node = getSET(set, getParent(node));
            set->display(fp, getNode(node));
            }
        fprintf(fp, "\n");
        }

    return TRUE;

    }

/*** PRIVATE FUNCTION DEFINITIONS ***/
setnode *newNode(void *val){

    setnode *node = malloc(sizeof(setnode));
    node->store = val;
    node->index = DEFAULT;
    node->parent = DEFAULT;
    node->rep = node;
    node->rank = 1;

    return node;

    }

void *getNode(setnode *node){return node->store;}
setnode *getRep(setnode *node){return node->rep;}
void setRep(setnode *node, setnode *r){node->rep = r;}
int getIndex(setnode *node){return node->index;}
void setIndex(setnode *node, int i){node->index = i;}
int getRank(setnode *node){return node->rank;}
void setRank(setnode *node, int r){node->rank = r;}
int getParent(setnode *node){return node->parent;}
void setParent(setnode *node, int p){node->parent = p;}
setnode *getSET(SET *set, int index){return getDA(set->array, index);}
int isrep(setnode *node){

    setnode *r = getRep(node);
    if(getIndex(node) == getIndex(r)) return TRUE;
    else return FALSE;

    }
