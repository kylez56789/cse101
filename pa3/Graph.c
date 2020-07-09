// Kyle Zhang
// kmzhang
// CSE101
// pa3
// April 25, 2020

#include "Graph.h"

typedef struct GraphObj {
    List* lists;
    int* colors;
    int* parents;
    int* distance;
    int order;
    int size;
    int source;
} GraphObj;

Graph newGraph(int n) {
   Graph G = malloc(sizeof(GraphObj));
   G->lists = calloc(n+1, sizeof(List));
   G->colors = calloc(n+1, sizeof(int));
   G->parents = calloc(n+1, sizeof(int));
   G->distance = calloc(n+1, sizeof(int));
   for (int i = 1; i <= n; i++) {
      G->lists[i] = newList();
      G->colors[i] = WHITE;
      G->distance[i] = INF;
      G->parents[i] = NIL;
   }
   G->order = n;
   G->size = 0;
   G->source = NIL;
   return G;
}

void freeGraph(Graph* pG) {
   if (*pG != NULL && pG != NULL) {
      for (int i = 1; i <= (*pG)->order; i++) {
         freeList(&((*pG)->lists[i]));
      }
      free((*pG)->lists);
      free((*pG)->colors);
      free((*pG)->parents);
      free((*pG)->distance);
      free(*pG);
   }
}

int getOrder(Graph G) {
   if (G == NULL) {
      fprintf(stderr, "Graph Error: getOrder() - Graph is NULL\n");
      exit(EXIT_FAILURE);
   }
   return G->order;
}

int getSize(Graph G){
   if (G == NULL) {
      fprintf(stderr, "Graph Error: getSize() - Graph is NULL\n");
      exit(EXIT_FAILURE);
   }
   return G->size;
}

int getSource(Graph G){
   if (G == NULL) {
      fprintf(stderr, "Graph Error: getSource() - Graph is NULL\n");
      exit(EXIT_FAILURE);
   }
   return G->source;
}

int getParent(Graph G, int u){
   if (G == NULL) {
      fprintf(stderr, "Graph Error: getParent() - Graph is NULL\n");
      exit(EXIT_FAILURE);
   } else if (G->source == NIL) {
      return NIL;
   } else {
      return G->parents[u];
   }
}

int getDist(Graph G, int u){
   if (G == NULL) {
      fprintf(stderr, "Graph Error: getDist() - Graph is NULL\n");
      exit(EXIT_FAILURE);
   } else if (G->source == 0) {
      return INF;
   } else {
      return G->distance[u];
   }
}

void getPath(List L, Graph G, int u){
   if (G == NULL) {
      fprintf(stderr, "Graph Error: getPath() - Graph is NULL\n");
      exit(EXIT_FAILURE);
   } else if (!(1 <= u && u <= getOrder(G))) {
      fprintf(stderr, "Graph Error: getPath() - Graph is NULL\n");
      exit(EXIT_FAILURE);
   } else if (u == G->source) {
      append(L, u);
   } else if (G->distance[u] == INF) {
      append(L, NIL);
   } else {
		getPath(L, G, G->parents[u]);
      append(L, u);
   }
}

void makeNull(Graph G){
   if (G == NULL) {
      fprintf(stderr, "Graph Error: makeNull() - Graph is NULL\n");
      exit(EXIT_FAILURE);
   } else {
      for (int i = 1; i <= G->size; i++) {
         clear(G->lists[i]);
         G->colors[i] = WHITE;
         G->parents[i] = NIL;
         G->distance[i] = INF;
      }
   }
}

void addEdge(Graph G, int u, int v){
   if (G == NULL) {
      fprintf(stderr, "Graph Error: addEdge() - Graph is NULL\n");
      exit(EXIT_FAILURE);
   } else if (!(1 <= u && u <= getOrder(G)) || !(1 <= v && v <= getOrder(G))){
      fprintf(stderr, "Graph Error: addEdge() - u or v are not valid vertexes\n");
      exit(EXIT_FAILURE);
   } else {
      addArc(G, u, v);
      addArc(G, v, u);
		(G->size) -= 1;
   }
}

void addArc(Graph G, int u, int v){
   if (G == NULL) {
      fprintf(stderr, "Graph Error: addArc() - Graph is NULL\n");
      exit(EXIT_FAILURE);
   } else if (!(1 <= u && u <= getOrder(G)) || !(1 <= v && v <= getOrder(G))){
      fprintf(stderr, "Graph Error: addArc() - u or v are not valid vertexes\n");
      exit(EXIT_FAILURE);
   } else {
      moveFront(G->lists[u]);
      while(index(G->lists[u]) >= 0 && v > get(G->lists[u])) {
         if (v == get(G->lists[u])) {
            return;
         }
         moveNext(G->lists[u]);
      }
      if(index(G->lists[u]) == -1) {
         append(G->lists[u], v);
      } else {
         insertBefore(G->lists[u], v);
      }
      (G->size) += 1;
   }
}

void BFS(Graph G, int s){
   if (G == NULL) {
      fprintf(stderr, "Graph Error: BFS() - Graph is NULL\n");
      exit(EXIT_FAILURE);
   }
   int u = 0, i = 0, v = 0;
   G->source = s;
   for (i = 1; i <= G->order; i++) {
         G->colors[i] = WHITE;
         G->distance[i] = INF;
         G->parents[i] = NIL;
   }
   G->colors[s] = GRAY;
   G->distance[s] = 0;
   G->parents[s] = NIL;
   List Q = newList();
   append(Q, s);
   while (length(Q) != 0) {
      u = front(Q);
      deleteFront(Q);
      moveFront(G->lists[u]);
      while (index(G->lists[u]) >= 0) {
         v = get(G->lists[u]);
         if (G->colors[v] == WHITE) {
            G->colors[v] = GRAY;
            G->distance[v] = G->distance[u] + 1;
            G->parents[v] = u;
            append(Q, v);
         }
         moveNext(G->lists[u]);
      }
      G->colors[u] = BLACK;
   }
   freeList(&Q);
}

void printGraph(FILE* out, Graph G){
   int i;
   for (i = 1; i <= G->order; i++) {
      fprintf(out, "%d: ", i);
      printList(out, G->lists[i]);
		if (i == G->order) {
			break;
		}
      fprintf(out, "\n");
   }
}
