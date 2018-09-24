#ifndef __EDGE_H__
#define __EDGE_H__

#include <stdio.h>

typedef struct Edge edge;

extern edge *newEdge(int, int, int);
extern int getEdgeSmall(edge *);
extern int getEdgeLarge(edge *);
extern int getEdgeWeight(edge *);
extern int getEdgeVisit(edge *);
extern void setEdgeSmall(edge *, int);
extern void setEdgeLarge(edge *, int);
extern void setEdgeWeight(edge *, int);
extern void setEdgeVisit(edge *, int);
extern void displayEdge(FILE *, void *);
extern int compareEdgeVertex(void *, void *);
extern int compareEdgeWeight(void *, void *);

#endif
