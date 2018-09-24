#ifndef __VERT_H__
#define __VERT_H__

#include <stdio.h>
#include "da.h"

typedef struct Vertex vertex;

extern vertex *newVertex(int);
extern int getVertex(vertex *);
extern int getVertexIndex(vertex *);
extern int getVertexVisit(vertex *);
extern vertex *getVertexParent(vertex *);
extern void setVertex(vertex *, int);
extern void setVertexIndex(vertex *, int);
extern void setVertexParent(vertex *, vertex *);
extern int compareVertex(void *, void *);
extern void setVertexVisit(vertex *, int);
extern void displayVertex(FILE *, void *);
extern DA *getAdjList(vertex *);
extern void insertAdjList(vertex *, void *);

#endif
