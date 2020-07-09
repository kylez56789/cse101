// Kyle Zhang
// kmzhang
// CSE101
// pa3
// April 25, 2020

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   int i, n=35;
   List  C = newList();
   Graph G = NULL;

   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);
   printGraph(stdout, G);
   printf("\n");
   BFS(G, 9);
   getPath(C, G, 1);
   fprintf(stdout, "Path of 1 = ");
   printList(stdout, C);
   fprintf(stdout, "\n");

   for (i = 0; i < n; i++) {
      BFS(G, i);
      clear(C);
      getPath(C, G, 1);
      printf("Source: %d\n", getSource(G));
      if (getDist(G, 1) == INF){
         printf("Distance of 1 is infinity\n");
      } else {
         printf("Distance of 1: %d\n", getDist(G, 1));
      }
      if (getDist(G, 5) == INF){
         printf("Distance of 5 is infinity\n");
      } else {
         printf("Distance of 5: %d\n", getDist(G, 5));
      }
      if (getParent(G, 1) == NIL) {
         printf("Parent of 1 is NIL\n");
      } else {
         printf("Parent of 1: %d\n", getParent(G, 1));
      }
      if (getParent(G, 5) == NIL) {
         printf("Parent of 5 is NIL\n");
      } else {
         printf("Parent of 5: %d\n", getParent(G, 5));
      }
      printf("Path from 1 to %d is ", i);
      printList(stdout, C);
      printf("\n");
   }
   printf("Size of G = %d\n", getSize(G));
   printf("Order of G = %d\n", getOrder(G));
   makeNull(G);
   printGraph(stdout, G);
   
   freeList(&C);
   freeGraph(&G);
   return(0);
}
