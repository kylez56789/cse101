// Kyle Zhang
// kmzhang
// CSE101
// pa4
// May 1, 2020
// Graph.h

#ifndef PA3_GRAPH_H
#define PA3_GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#define UNDEF -1
#define NIL -2
#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct GraphObj* Graph;
/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);
/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);


#endif //PA3_GRAPH_H
