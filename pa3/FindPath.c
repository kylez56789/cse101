// Kyle Zhang
// kmzhang
// CSE101
// pa3
// April 25, 2020

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include <string.h>

int main(int argc, char* argv[]) {
   FILE *in, *out;
   int u = 0, v = 0, n = 0;
   if (argc != 3) {
      fprintf(stderr, "Usage: FindPath <input file> <output file>\n");
      exit(EXIT_FAILURE);
   }
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   fscanf(in, "%d", &n);
   Graph G = newGraph(n);
   List A = newList();
   List B = newList();
   List path = newList();
   if (n > 0) {
      while (1) {
         fscanf(in, "%d %d", &u, &v);
         if (u == 0 || v == 0) {
            break;
         }
         addEdge(G, u, v);
      }
   }
   if (n > 0) {
      while (1) {
         fscanf(in, "%d %d", &u, &v);
         if (u == 0 || v == 0) {
            break;
         }
         append(A, u);
         append(B, v);
      }
   }
   printGraph(out, G);
   moveFront(A);
   moveFront(B);
   while (index(A) >= 0) {
      clear(path);
      BFS(G, get(A));
      getPath(path, G, get(B));
      if (getDist(G, get(B)) == INF) {
         fprintf(out, "\n\nThe distance from %d to %d is infinity", get(A), get(B));
         fprintf(out, "\nNo %d-%d path exists", get(A), get(B));
      } else {
         fprintf(out, "\n\nThe distance from %d to %d is %d", get(A), get(B), getDist(G, get(B)));
         fprintf(out, "\nA shortest %d-%d path is: ", get(A), get(B));
         printList(out, path);
      }
      moveNext(A);
      moveNext(B);
   }
	fprintf(out, "\n\n");
   freeList(&A);
   freeList(&B);
   freeList(&path);
   freeGraph(&G);
   return EXIT_SUCCESS;
}
