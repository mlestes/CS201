#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//LOCAL INCLUDES
#include "edge.h"
#include "io.h"

/*****************************************************************************/
/* edge.c BY Murray Estes                                                    */
/* PUPRPOSE: To implement an edge object for storing edges of a graph.       */
/* METHOD DESCRIPTIONS:                                                      */
/*     edge *newEdge(int, int, int);                                         */
/*         Creates a new edge object.                                        */
/*                                                                           */
/*     int getEdgeSmall(edge *);                                             */
/*         Returns the smaller of the two vertices.                          */
/*                                                                           */
/*     int getEdgeLarge(edge *);                                             */
/*         Returns the larger of the two vertices.                           */
/*                                                                           */
/*     int getEdgeWeight(edge *);                                            */
/*         Returns the weight of the edge.                                   */
/*                                                                           */
/*     int getEdgeVisit(edge *);                                             */
/*         Returns the value associated with the algorithm's search pattern. */
/*                                                                           */
/*     void setEdgeSmall(edge *, int);                                       */
/*         Sets the designated vertex value.                                 */
/*                                                                           */
/*     void setEdgeLarge(edge *, int);                                       */
/*         Sets the designated vertex value.                                 */
/*                                                                           */
/*     void setEdgeWeight(edge *, int);                                      */
/*         Sets the edge's weight.                                           */
/*                                                                           */
/*     void setEdgeVisit(edge *, int);                                       */
/*         Sets the edge's visit value.                                      */
/*                                                                           */
/*     void displayEdge(FILE *, void *);                                     */
/*         Prints the given edge to the supplied outstream.                  */
/*                                                                           */
/*     int compareEdgeVertex(void *, void *);                                */
/*         Returns a value used to compare vertices of a pair of edges.      */
/*                                                                           */
/*     int compareEdgeWeight(void *, void *);                                */
/*         Returns a value used to compare weights of a pair of edges.       */
/*                                                                           */
/*****************************************************************************/

/*** CONSTANTS ***/
#define TRUE 1
#define FALSE 0

/*** STRUCTS ***/
struct Edge{

    int small; 
    int large;
    int weight;
    int visit;

    };

/*** PRIVATE FUNCTION DECLARATIONS ***/
//none

/*** PUBLIC FUNCTION DEFINITIONS ***/
edge *newEdge(int s, int l, int w){

    edge *e = malloc(sizeof(edge));
    if(e == 0) fatal("Error: Failed to allocate memory for edge object.\n");
    e->small = s;
    e->large = l;
    e->weight = w;
    e->visit = FALSE;

    return e;

    }

int getEdgeSmall(edge *e){return e->small;}
int getEdgeLarge(edge *e){return e->large;}
int getEdgeWeight(edge *e){return e->weight;}
int getEdgeVisit(edge *e){return e->visit;}
void setEdgeSmall(edge *e, int n){e->small = n;}
void setEdgeLarge(edge *e, int n){e->large = n;}
void setEdgeWeight(edge *e, int n){e->weight = n;}
void setEdgeVisit(edge *e, int v){e->visit = v;}
void displayEdge(FILE *fp, void *e){

    edge *ed = (edge *) e;
    fprintf(fp, "%d(%d)%d", ed->small, ed->large, ed->weight);

    }

int compareEdgeVertex(void *a, void *b){

    edge *x = (edge *) a; edge *y = (edge *) b;
    if(x->small == y->small) return x->large - y->large;
    else return x->small - y->small; 

    }

int compareEdgeWeight(void *a, void *b){

    edge *x = (edge *) a; edge *y = (edge *) b;
    if(x->weight - y->weight == 0) return compareEdgeVertex(a, b);
    else return x->weight - y->weight;
    }

/*** PRIVATE FUNCTION DEFINITIONS ***/
//none
