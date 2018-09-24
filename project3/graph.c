#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//LOCAL INCLUDES
#include "graph.h"
#include "sort.h"
#include "vert.h"
#include "edge.h"
#include "set.h"
#include "queue.h"
#include "rbt.h"

/*****************************************************************************/
/* graph.c BY Murray Estes                                                   */
/* PUPRPOSE: To implement kruskal's algorithm and a Breadth-First Search.    */
/* METHOD DESCRIPTIONS:                                                      */
/*     void kruskal(SET *, DA *, DA *);                                      */
/*         Implements Kruskal's algorithm.                                   */
/*                                                                           */
/*     void BFS(FILE *, vertex *, RBT *);                                    */
/*         Implements a modified Breadth-First Search that doubles as a      */
/*         display function.                                                 */
/*                                                                           */
/*****************************************************************************/

/*** CONSTANTS ***/
#define TRUE 1
#define FALSE 0
#define WHITE 0
#define GRAY 1
#define BLACK 2

/*** STRUCTS ***/
//none

/*** PRIVATE FUNCTION DECLARATIONS ***/
static edge *findEdge(RBT *, int, int);

/*** PUBLIC FUNCTION DEFINITIONS ***/
void kruskal(SET *set, DA *varr, DA *earr){

    RBT *tree = newRBT(displayVertex, compareVertex);
    int ued = FALSE;

/*** for each vertex v, makeSET(v) ***/
    for(int i = 0; i < sizeDA(varr); i++){
        vertex *v = getDA(varr, i);
        int index = makeSET(set, v);
        setVertexIndex(v, index);
        insertRBT(tree, v);
        }

/*** sort the edges into nondecreasing order by weight ***/
    msort(earr, compareEdgeWeight);

/*** for each edge taken, union the vertices ***/
    for(int i = 0; i < sizeDA(earr); i++){
        edge *e = getDA(earr, i);
        vertex *s = findRBTNode(tree, newVertex(getEdgeSmall(e)));
        vertex *l = findRBTNode(tree, newVertex(getEdgeLarge(e)));
        ued = unionSET(set, getVertexIndex(s), getVertexIndex(l));
        if(ued == TRUE){
            insertAdjList(s, l);
            insertAdjList(l, s);
            }
        ued = FALSE;
        }

    }

void BFS(FILE * fp, vertex *s, RBT *edges){

    int weight = 0; int lvl = 0; int count = 0; int limit = 1; int qued = 0;
    DA *lvlist = newDA(displayVertex);
    QUEUE *q = newQUEUE(0);
    setVertexVisit(s, GRAY);
    enqueue(q, s); 
    while(sizeQUEUE(q) > 0){
        if(count == 0) fprintf(fp, "%d : ", lvl);
        else fprintf(fp, " ");
        vertex *u = dequeue(q); count++;
        vertex *p = getVertexParent(u);
        edge *e = 0;
        if(p) e = findEdge(edges, getVertex(u), getVertex(p));
        if(e) weight += getEdgeWeight(e);
        fprintf(fp, "%d", getVertex(u));
        if(p) fprintf(fp, "(%d)%d", getVertex(p), getEdgeWeight(e));
        DA *list = getAdjList(u);
        for(int i = 0; i < sizeDA(list); i++){
            vertex *v = getDA(list, i);
            if(getVertexVisit(v) == WHITE){
                setVertexVisit(v, GRAY);
                setVertexParent(v, u);
                insertDA(lvlist, v); qued++;
                }
            }
        setVertexVisit(u, BLACK);
        if(count == limit){
            limit = qued;
            qued = 0;
            count = 0;
            lvl++;
            msort(lvlist, compareVertex);
            for(int i = 0; i < sizeDA(lvlist); i++)
                enqueue(q, getDA(lvlist, i));
            extractDA(lvlist);
            fprintf(fp, "\n");
            }
        }
    fprintf(fp, "total weight: %d\n", weight);
    fprintf(fp, "----\n");

    }

/*** PRIVATE FUNCTION DEFINITIONS ***/
edge *findEdge(RBT *tree, int u, int v){
    
    edge *e =findRBTNode(tree, newEdge(u, v, 1));
    if(e == 0) e = findRBTNode(tree, newEdge(v, u, 1));
 
    return e;

    }
