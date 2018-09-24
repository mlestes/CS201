#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//LOCAL INCLUDES
#include "vert.h"
#include "io.h"
#include "da.h"

/*****************************************************************************/
/* vert.c BY Murray Estes                                                    */
/* PUPRPOSE: To create a vertex class that uses integers as lables for       */
/*           vertices on a graph.                                            */
/* METHOD DESCRIPTIONS:                                                      */
/*     vertex *newVertex(int);                                               */
/*         Creates a new vertex object.                                      */
/*                                                                           */
/*     int getVertex(vertex *);                                              */
/*        Returns the stored integer.                                        */
/*                                                                           */
/*     int getVertexIndex(vertex *);                                         */
/*         Returns the index that the Vertex is stored in a disjoint set     */
/*         object.                                                           */
/*                                                                           */
/*     int getVertexVisit(vertex *);                                         */
/*         Returns the visited label used in BFS.                            */
/*                                                                           */
/*     vertex *getVertexParent(vertex *);                                    */
/*         Returns the parent, or predecessor, of the vertex. Used primarily */
/*         in BFS.                                                           */
/*                                                                           */
/*     void setVertex(vertex *, int);                                        */
/*         Sets a new value into the vertex object.                          */
/*                                                                           */
/*     void setVertexIndex(vertex *, int);                                   */
/*         Sets the new value for the index of the vertex object.            */
/*                                                                           */
/*     void setVertexParent(vertex *, vertex *);                             */
/*         Sets the parent pointer to another vertex object.                 */
/*                                                                           */
/*     int compareVertex(void *, void *);                                    */
/*         Compares the stored values of two vertices.                       */
/*                                                                           */
/*     void setVertexVisit(vertex *, int);                                   */
/*         Sets the visit label used in BFS or other search algorithms.      */
/*                                                                           */
/*     void displayVertex(FILE *, void *);                                   */
/*         Displays the given vertex to the supplied outstream.              */
/*                                                                           */
/*     DA *getAdjList(vertex *);                                             */
/*         Returns the internal adjacency list.                              */
/*                                                                           */
/*     void insertAdjList(vertex *, void *);                                 */
/*         Inserts a new item into the adjacency list.                       */
/*                                                                           */
/*****************************************************************************/

/*** CONSTANTS ***/
#define TRUE 1
#define FALSE 0

/*** STRUCTS ***/
struct Vertex{

    int store;
    struct Vertex *parent;
    int index;
    int visit;
    DA *adj;    

    };

/*** PRIVATE FUNCTION DECLARATIONS ***/
//none

/*** PUBLIC FUNCTION DEFINITIONS ***/
vertex *newVertex(int value){

    vertex *v = malloc(sizeof(vertex));
    if(v == 0) fatal("Error: Failed to allocate memory for Vertex object.\n");
    v->store = value;
    v->parent = 0;
    v->index = 0;
    v->visit = FALSE;
    v->adj = newDA(displayVertex);

    return v;

    }

int getVertex(vertex *v){return v->store;}
int getVertexIndex(vertex *v){return v->index;}
int getVertexVisit(vertex *v){return v->visit;}
vertex *getVertexParent(vertex *v){return v->parent;}
void setVertex(vertex *v, int i){v->store = i;}
void setVertexIndex(vertex *v, int i){v->index = i;}
void setVertexVisit(vertex *v, int i){v->visit = i;}
void setVertexParent(vertex *v, vertex *p){v->parent = p;}
int compareVertex(void *a, void *b){

    vertex *x = (vertex *) a; vertex *y = (vertex *) b;
    return x->store - y->store;

    }

void displayVertex(FILE *fp, void *obj){

    vertex *v = (vertex *) obj;
    fprintf(fp, "%d", v->store);

    }

DA *getAdjList(vertex *v){return v->adj;}
void insertAdjList(vertex *v, void *val){insertDA(v->adj, val);}
/*** PRIVATE FUNCTION DEFINITIONS ***/
//none
