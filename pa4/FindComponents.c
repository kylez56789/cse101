// Kyle Zhang
// kmzhang
// CSE101
// pa4
// May 1, 2020
// FindComponents.c

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include <string.h>

int main(int argc, char* argv[]) {
   FILE *in, *out;
   int u = 0, v = 0, n = 0, i = 1, c = 0;
   if (argc != 3) {
      fprintf(stderr, "Usage: FindComponents <input file> <output file>\n");
      exit(EXIT_FAILURE);
   }
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   fscanf(in, "%d", &n);
   Graph G = newGraph(n);
   List A = newList();
   if (n > 0) {
      while (1) {
         fscanf(in, "%d %d", &u, &v);
         if (u == 0 || v == 0) {
            break;
         }
         addArc(G, u, v);
      }
   }
   List L = newList();
   for (i = 1; i < getOrder(G); i++) {
      append(L, i);
   }
   fprintf(out, "Adjacency list representation of G:\n");
   printGraph(out, G);
   fprintf(out, "\n\n");
   DFS(G, L);
   List S = copyList(L);
   Graph T = transpose(G);
   DFS(T, S);
   moveFront(S);
   while (1) {
      if (getParent(T, get(S)) == NIL) {
         c++;
      }
      if (index(S) == getOrder(T) - 1) {
         break;
      }
      moveNext(S);
   }
   fprintf(out, "G contains %d strongly connected components:\n", c);
   moveBack(S);
   c = 1;
   while (index(S) >= 0) {
      clear(A);
      while (getParent(T, get(S)) != NIL) {
         prepend(A, get(S));
         movePrev(S);
      }
      prepend(A, get(S));
      movePrev(S);
      fprintf(out, "Component %d: ", c);
      printList(out, A);
      fprintf(out, "\n");
      c++;
   }
   freeList(&L);
   freeList(&A);
   freeList(&S);
   freeGraph(&T);
   freeGraph(&G);
	fclose(out);
	fclose(in);
   return EXIT_SUCCESS;
}
