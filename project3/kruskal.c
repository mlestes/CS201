#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
//LOCAL INCLUDES
#include "graph.h"
#include "sort.h"
#include "edge.h"
#include "da.h"
#include "set.h"
#include "rbt.h"
#include "vert.h"
#include "io.h"

/*** CONSTANTS ***/
#define TRUE 1
#define FALSE 0
#define EMPTY -1
#define WHITE 0
#define GRAY 1
#define BLACK 2

/*** STRUCTS ***/
//none

/*** PRIVATE FUNCTION DECLARATIONS ***/
static FILE *openFILE(int, char **);
static int buildArrays(FILE *, DA *, DA *, RBT *);
static void displayForest(FILE *, RBT *, DA *);

/*** PUBLIC FUNCTION DEFINITIONS ***/
int main(int argc, char **argv){

/*** CREATE THE DATA STRUCTURES ***/
    FILE *fp = openFILE(argc, argv);
    DA *varr = newDA(displayVertex);
    DA *earr = newDA(displayEdge);
    RBT *tree = newRBT(displayEdge, compareEdgeVertex);
    SET *set = newSET(displayVertex);

/*** READ IN THE FILE ***/
    buildArrays(fp, varr, earr, tree);

/*** BUILD THE MINIMUM SPANNING FOREST ***/
    kruskal(set, varr, earr);

/*** PRINT THE FOREST ***/
    displayForest(stdout, tree, varr);

    return 0;

    }

/*** PRIVATE FUNCTION DEFINITIONS ***/
FILE *openFILE(int c, char **v){

    if(c < 2) 
        fatal("Error: insufficient arguments.\nUsage: kruskal [FILE]\n");
    if(strcmp(v[1], "-v") == 0){
        printf("Murray L. Estes\n");
        exit(0);
        }
    FILE *fp = fopen(v[1], "r");
    if(fp == 0)
        fatal(
             "Error: Unable to open \"%s\". Check to see if the file exists.\n",
              v[1]);

    return fp;

    }

int buildArrays(FILE *fp, DA *varr, DA *earr, RBT *tree){

    edge *z; int max = EMPTY;
    char *a = readFILE(fp); char *b = readFILE(fp); char *c = readFILE(fp);
    while(feof(fp) == FALSE){
        int i = atoi(a); int j = atoi(b); int k = 1;
        if(i > max) max = i;
        if(j > max) max = j;
        if(strcmp(c, ";") != 0){
            k = atoi(c);
            readFILE(fp);
            }
        if(i < j) z = newEdge(i, j, k);
        else z = newEdge(j, i, k);
        edge *test = findRBTNode(tree, z);
        if(test == FALSE){
            insertRBT(tree, z);
            insertDA(earr, z);
            }
        else if(compareEdgeWeight(z, test) < 0) setEdgeWeight(test, k);
        a = readFILE(fp); b = readFILE(fp); c = readFILE(fp);
        }
    int *arr = malloc(sizeof(int) * (max + 1));
    for(int d = 0; d < max + 1; d++) arr[d] = EMPTY;
    for(int d = 0; d < sizeDA(earr); d++){
        edge *e = getDA(earr, d);
        int s = getEdgeSmall(e);
        int l = getEdgeLarge(e);
        if(arr[s] == EMPTY){
            arr[s] = s;
            insertDA(varr, newVertex(s));
            }
        if(arr[l] == EMPTY){
            arr[l] = l;
            insertDA(varr, newVertex(l));
            }
        }

    return max;

    }

void displayForest(FILE *fp, RBT *tree, DA *varr){

/*** SORT THE VERTICES TO WHERE THE SMALLEST IS FIRST ***/
    msort(varr, compareVertex);
    for(int i = 0; i < sizeDA(varr); i++) setVertexVisit(getDA(varr, i), WHITE);

/*** WALK THE VERTEX ARRAY AND VIST THE VERTICES ***/
    if(sizeDA(varr) == 0) printf("0 :\n");
    else{
        for(int i = 0; i < sizeDA(varr); i++){
            vertex *v = getDA(varr, i);
            if(getVertexVisit(v) == WHITE) BFS(fp, v, tree);
            }
        }
    
    }
