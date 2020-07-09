// Kyle Zhang
// kmzhang
// CSE101
// pa4
// May 1, 2020
// Graph.c

#include "Graph.h"

typedef struct GraphObj {
    List* lists;
    int* parents;
    int* finish;
    int* discover;
    int* colors;
    int order;
    int size;
} GraphObj;

Graph newGraph(int n) {
   Graph G = malloc(sizeof(GraphObj));
   G->lists = calloc(n+1, sizeof(List));
   G->parents = calloc(n+1, sizeof(int));
   G->discover = calloc(n+1, sizeof(int));
   G->finish = calloc(n+1, sizeof(int));
   G->colors = calloc(n+1, sizeof(int));
   for (int i = 1; i <= n; i++) {
      G->lists[i] = newList();
      G->finish[i] = UNDEF;
      G->discover[i] = UNDEF;
      G->parents[i] = NIL;
      G->colors[i] = WHITE;
   }
   G->order = n;
   G->size = 0;
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
      free((*pG)->finish);
      free((*pG)->discover);
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

int getParent(Graph G, int u){
   if (G == NULL) {
      fprintf(stderr, "Graph Error: getParent() - Graph is NULL\n");
      exit(EXIT_FAILURE);
   } else {
      return G->parents[u];
   }
}

int getDiscover(Graph G, int u){
   if (G == NULL) {
      fprintf(stderr, "Graph Error: getDiscover() - Graph is NULL\n");
      exit(EXIT_FAILURE);
   } else {
      return G->discover[u];
   }
}

int getFinish(Graph G, int u){
   if (G == NULL) {
      fprintf(stderr, "Graph Error: getFinish() - Graph is NULL\n");
      exit(EXIT_FAILURE);
   } else {
      return G->finish[u];
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

void visit(Graph G, int u, int* t) {
   (*t)++;
   G->discover[u] = (*t);
   G->colors[u] = GRAY;
   moveFront(G->lists[u]);
   while (index(G->lists[u]) >= 0) {
      if (G->colors[get(G->lists[u])] == WHITE) {
         G->parents[get(G->lists[u])] = u;
         visit(G, get(G->lists[u]), t);
      }
      moveNext(G->lists[u]);
   }
   G->colors[u] = BLACK;
   (*t)++;
   G->finish[u] = (*t);
}

void DFS(Graph G, List S){
   int i = 0, time = 0;
   for (i = 1; i <= G->order; i++) {
      G->colors[i] = WHITE;
      G->parents[i] = NIL;
   }
   moveFront(S);
   while (index(S) >= 0) {
      if (G->colors[get(S)] == WHITE) {
         visit(G, get(S), &time);
      }
      moveNext(S);
   }
   List A = copyList(S);
   for (i = 1; i <= G->order; i++) {
      moveFront(A);
      while(index(A) >= 0) {
         if (get(A) == i) delete(A);
         moveNext(A);
      }
      moveBack(A);
      while(index(A) >= 0 && G->finish[i] < G->finish[get(A)]) {
         movePrev(A);
      }
      if(index(A) == -1) {
         prepend(A, i);
      } else {
         insertAfter(A, i);
      }
   }
   moveFront(A);
   clear(S);
   while (index(A) >= 0) {
      prepend(S, get(A));
      moveNext(A);
   }
   freeList(&A);
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

Graph transpose(Graph G){
   if (G == NULL) {
      fprintf(stderr, "Graph Error: transpose() - Graph is NULL\n");
      exit(EXIT_FAILURE);
   } else {
      int i = 0;
      Graph A = newGraph(getOrder(G));
      for (i = 1; i <= getOrder(G); i++) {
         moveFront(G->lists[i]);
         while (index(G->lists[i]) >= 0) {
            addArc(A, get(G->lists[i]), i);
            moveNext(G->lists[i]);
         }
      }
      return A;
   }
}

Graph copyGraph(Graph G){
   if (G == NULL) {
      fprintf(stderr, "Graph Error: transpose() - Graph is NULL\n");
      exit(EXIT_FAILURE);
   } else {
      int i = 0;
      Graph A = newGraph(getOrder(G));
      for (i = 1; i <= getOrder(G); i++) {
         A->lists[i] = copyList(G->lists[i]);
         A->parents[i] = G->parents[i];
         A->discover[i] = G->discover[i];
         A->finish[i] = G->finish[i];
      }
      A->order = G->order;
      A->size = G->size;
      return A;
   }
}
