#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include "set.h"
#include "da.h"
#include "rbt.h"
#include "vert.h"

extern void kruskal(SET *, DA *, DA *);
extern void BFS(FILE *, vertex *, RBT *);

#endif
