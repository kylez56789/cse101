//
// Created by kylez on 4/11/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main(int argc, char* argv[]){

   List A = newList();
   List B = newList();
   List C = NULL;
	List L = newList();
	if (indexList(L) != -1) {
		printf("1");
	}
	else {
   	printf("0");
	}
	freeList(&L);
   int i;

   for(i=1; i<=20; i++){
      append(A,i);
      prepend(B,i);
   }

   printList(stdout,A);
   printf("\n");
   printList(stdout,B);
   printf("\n");

   for(moveFront(A); listIndex(A)>=0; moveNext(A)){
      printf("%ld ", get(A));
   }
   printf("\n");
   for(moveBack(B); listIndex(B)>=0; movePrev(B)){
      printf("%ld ", get(B));
   }
   printf("\n");

   C = copyList(A);
   printf("%s\n", listEquals(A,B)?"true":"false");
   printf("%s\n", listEquals(B,C)?"true":"false");
   printf("%s\n", listEquals(C,A)?"true":"false");


   moveFront(A);
   for(i=0; i<5; i++) moveNext(A); // at index 5
   insertBefore(A, -1);            // at index 6
   for(i=0; i<9; i++) moveNext(A); // at index 15
   insertAfter(A, -2);
   for(i=0; i<5; i++) movePrev(A); // at index 10
   delete(A);
   printList(stdout, A);
   printf("\n");
   printf("%d\n", length(A));
   printf("%d\n", length(A));
   moveFront(A);
   set(A, -15);
   moveFront(A);
   moveNext(A);
   moveNext(A);
   set(A, 20);
   printList(stdout, A);
	clear(A);
	append(A, 25);
	clear(B);
	append(B, 10);
	List D = uprod(A, B);
	List E = uadd(A, B);
	List F = usub(A, B);
   freeList(&A);
   freeList(&B);
   freeList(&C);
	freeList(&D);
	freeList(&E);
	freeList(&F);
   return(0);
}
