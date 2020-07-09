// Kyle Zhang
// kmzhang
// CSE101
// pa4
// May 1, 2020
// GraphTest.c

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   int i, n=8, c=0;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 2,3);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,4);
   addArc(G, 3,7);
   addArc(G, 4,3);
   addArc(G, 4,8);
   addArc(G, 5,1);
   addArc(G, 5,6);
   addArc(G, 6,7);
   addArc(G, 7,6);
   addArc(G, 7,8);
   addArc(G, 8,8);
   printGraph(stdout, G);

   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++) {
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   List A = newList();
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
   fprintf(stdout, "G contains %d strongly connected components:\n", c);
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
      fprintf(stdout, "Component %d: ", c);
      printList(stdout, A);
      fprintf(stdout, "\n");
      c++;
   }
   fprintf(stdout, "\n\n");
   freeList(&A);
   freeGraph(&G);
   freeList(&S);
   freeGraph(&T);
   freeGraph(&C);
   return(0);
}
