// Kyle Zhang
// kmzhang
// CSE101
// pa1
// March 31, 2019
// List.c
// Description: Source file for a List ADT

#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BASE 1000000000
#define POWER 9

typedef struct NodeObj {
   long data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj {
   Node front;
   Node back;
   Node cursor;
   int length;
   int curindex;
} ListObj;

Node newNode(long data) {
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

void freeNode(Node* pN) {
   if(pN != NULL && *pN != NULL ) {
      free(*pN);
      *pN = NULL;
   }
}

List newList() {
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->curindex = -1;
    return L;
}

void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {
        while(length(*pL) != 0) {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    } else {
        fprintf(stderr, "List error: freeList(List* pL) - cannot operate on a null list.");
        exit(1);
    }
}

int length(List L) {
    if(L == NULL) {
        fprintf(stderr, "List error: length(List L) - cannot operate on a null list.");
        exit(1);
    } else {
        return L->length;
    }
}

int index(List L) {
    if(L == NULL) {
        fprintf(stderr, "List error: index(List L) - cannot operate on a null list.");
        exit(1);
    } else {
        return L->curindex;
    }
}

long front(List L) {
    if(L == NULL) {
        fprintf(stderr, "List error: front(List L) - cannot operate on a null list.");
        exit(1);
    } else {
        return L->front->data;
    }
}

long back(List L) {
    if(L == NULL)
    {
        fprintf(stderr, "List error: back(List L) - cannot operate on a null list.");
        exit(1);
    } else {
        return L->back->data;
    }
}

long get(List L) {
    if(L == NULL)
    {
        fprintf(stderr, "List error: back(List L) - cannot operate on a null list.");
        exit(1);
    }
    else if(L->length == 0)
    {
        fprintf(stderr, "List error: back(List L) - length = 0.");
        exit(1);
    }
    else if(L->curindex == -1)
    {
        fprintf(stderr, "List error: get(List L) - current index undefined.");
        exit(1);
    }
    return L->cursor->data;
}

int listEquals(List A, List B){
    if(A == NULL)
    {
        fprintf(stderr, "List error: equals(List A, List B) - cannot operate on null list A.");
        exit(1);
    }
    else if(B == NULL)
    {
        fprintf(stderr, "List error: equals(List A, List B) - cannot operate on null list B.");
        exit(1);
    }
	 Node C = A->front;
	 Node D = B->front;
    if(A->length != B->length) {
        return 0;
    }
    for(; C != NULL && D != NULL; C = C->next, D = D->next){
	 	  if(C->data != D->data){
		      return 0;
		  }
    }
  	 return 1;
}

void clear(List L){
    if(L == NULL) {
        fprintf(stderr, "List error: clear(List L) - cannot operate on a null list.");
        exit(1);
    }
    while(L->length != 0) {
        deleteFront(L);
    }
}

void moveFront(List L){
    if(L == NULL)
    {
        fprintf(stderr, "List error: moveFront(List L) - cannot operate on a null list.");
        exit(1);
    }
    if(L->length > 0) {
        L->cursor = L->front;
        L->curindex = 0;
    }
}

void moveBack(List L){
    if(L == NULL)
    {
        fprintf(stderr, "List error: moveBack(List L) - cannot operate on a null list.");
        exit(1);
    }
    if(L->length > 0) {
        L->cursor = L->back;
        L->curindex = (L->length) - 1;
    }
}

void movePrev(List L){
    if(L == NULL)
    {
        fprintf(stderr, "List error: movePrev(List L) - cannot operate on a null list.");
        exit(1);
    }
    if (L->cursor != NULL){
        if(L->cursor != L->front) {
            L->cursor = L->cursor->prev;
            (L->curindex)--;
        } else {
            L->cursor = NULL;
            (L->curindex) = -1;
        }
    }
}

void moveNext(List L){
    if(L == NULL)
    {
        fprintf(stderr, "List error: moveNext(List L) - cannot operate on a null list.");
        exit(1);
    }
    else if(L->curindex == -1)
    {
        //if the index is undefined, then we do nothing
        return;
    }
    if (L->cursor != NULL){
        if(L->cursor != L->back) {
            L->cursor = L->cursor->next;
			(L->curindex)++;
        } else {
            L->cursor = NULL;
			(L->curindex) = -1;
        }
    }
}

void prepend(List L, long data) {
    if(L == NULL)
    {
        fprintf(stderr, "List error: prepend(List L, int data) - cannot operate on a null list.");
        exit(1);
    }
    if (L->length == 0) {
        L->front = L->back = newNode(data);
        (L->length)++;
        return;
    } else if (L->length == 1) {
        L->front = newNode(data);
        L->front->next = L->back;
        L->back->prev = L->front;
        (L->length)++;
        return;
    }
    Node N = newNode(data);
    N->next = L->front;
    L->front->prev = N;
    L->front = N;
    if (L->cursor != NULL) {
        (L->curindex)++;
    }
    (L->length)++;
}

void append(List L, long data) {
    if(L == NULL)
    {
        fprintf(stderr, "List error: append(List L, int data) - cannot operate on a null list.");
        exit(1);
    }
    if (L->length == 0) {
        L->front = L->back = newNode(data);
        (L->length)++;
        return;
    } else if (L->length == 1) {
        L->back = newNode(data);
        L->front->next = L->back;
        L->back->prev = L->front;
        (L->length)++;
        return;
    }
    Node N = newNode(data);
    N->prev = L->back;
    L->back->next = N;
    L->back = N;
    (L->length)++;
}

void insertBefore(List L, long data) {
    if(L == NULL)
    {
        fprintf(stderr, "List error: insertBefore(List L, int data) - cannot operate on a null list.");
        exit(1);
    }
    else if(L->length == 0)
    {
        fprintf(stderr, "List error: insertBefore(List L, int data) - length = 0.");
        exit(1);
    }
    else if(L->length == -1)
    {
        fprintf(stderr, "List error: insertBefore(List L, int data) - index undefined.");
        exit(1);
    }
    Node N = newNode(data);
	 if (L->cursor == L->front) {
        L->front = N;
		  N->prev = NULL;
    } else {
		  N->prev = L->cursor->prev;
		  N->prev->next = N;
	 }
    N->next = L->cursor;
    L->cursor->prev = N;
    (L->curindex)++;
    (L->length)++;
}

void insertAfter(List L, long data) {
    if(L == NULL)
    {
        fprintf(stderr, "List error: insertAfter(List L, int data) - cannot operate on a null list.");
        exit(1);
    }
    else if(L->length == 0)
    {
        fprintf(stderr, "List error: insertAfter(List L, int data) - length = 0.");
        exit(1);
    }
    else if(L->curindex == -1)
    {
        fprintf(stderr, "List error: insertAfter(List L, int data) - index undefined.");
        exit(1);
    }
    Node N = newNode(data);
	 if (L->cursor == L->back) {
		  L->back = N;
		  N->next = NULL;
    } else {
		  N->next = L->cursor->next;
		  N->next->prev = N;
	 }
    N->prev = L->cursor;
    L->cursor->next = N;
    (L->length)++;
}

void deleteFront(List L) {
    if(L == NULL)
    {
        fprintf(stderr, "List error: deleteFront(List L) - cannot operate on a null list.");
        exit(1);
    }
    else if(L->length == 0) //no elements to delete
    {
        fprintf(stderr, "List error: deleteFront(List L) - length = 0.");
        exit(1);
    }
    if (L->front == L->cursor) {
        delete(L);
    } else if (length(L) == 1) {
		  Node A = L->front;
		  L->front = NULL;
		  L->back = NULL;
		  freeNode(&A);
		  (L->length)--;
	 } else {
        Node A = L->front;
        L->front = A->next;
		  L->front->prev = NULL;
        freeNode(&A);
        if (L->cursor != NULL) {
            (L->curindex)--;
        }
		  (L->length)--;
    } 
}

void deleteBack(List L) {
    if(L == NULL)
    {
        fprintf(stderr, "List error: deleteBack(List L) - cannot operate on a null list.");
        exit(1);
    }
    else if(L->length == 0) //no elements to delete
    {
        fprintf(stderr, "List error: deleteBack(List L) - length = 0.");
        exit(1);
    }

    if (L->back == L->cursor) {
        delete(L);
	 } else if (length(L) == 1) {
        Node A = L->front;
        L->front = NULL;
        L->back = NULL;
        freeNode(&A);
		  (L->length)--;
    } else {
        Node A = L->back;
        L->back = A->prev;
        L->back->next = NULL;
        freeNode(&A);
		  (L->length)--;
    }
}

void delete(List L) {
    if(L == NULL)
    {
        fprintf(stderr, "List error: delete(List L) - cannot operate on a null list.");
        exit(1);
    }
    else if(L->length == 0) //no elements to delete
    {
        fprintf(stderr, "List error: delete(List L) - length = 0.");
        exit(1);
    }
    else if(L->curindex == -1) //cursor index undefined
    {
        fprintf(stderr, "List error: delete(List L) - cursor undefined.");
        exit(1);
    }
    if (L->cursor != NULL) {
		  Node A = L->cursor;
        if (L->length == 1) {
            L->front = NULL;
            L->back = NULL;
        } else {
            if (L->cursor == L->front) {
                L->front = L->cursor->next;
                L->front->prev = NULL;
            } else if (L->cursor == L->back) {
                L->back = L->cursor->prev;
                L->back->next = NULL;
            } else {
				    A->prev->next = A->next;
					 A->next->prev = A->prev;
			   }
        }
		  freeNode(&A);
    }
    L->cursor = NULL;
    L->curindex = -1;
    (L->length)--;
}

void set(List L, long x){
    if(L == NULL) {
        fprintf(stderr, "List error: set(List L, long x) - cannot operate on a null list.");
        exit(1);
    } else if (L->curindex == -1){
        fprintf (stderr, "List error: set(List L, long x) - cursor undefined.");
        exit(1);
    } else {
        insertAfter(L, x);
        delete(L);
    }
}

void printList(FILE* out, List L) {
    if(L == NULL)
    {
        fprintf(stderr, "List error: printList(FILE* out, List L) - cannot operate on a null list.");
        exit(1);
    }
    int first = 1;
    for (Node A = L->front; A != NULL; A = A->next) {
        if (first) {
            fprintf(out, "%ld", A->data);
            first = 0;
        } else {
            fprintf(out, " %ld", A->data);
        }
    }
}

List copyList(List L){
    if(L == NULL)
    {
        fprintf(stderr, "List error: copyList(List L) - cannot operate on a null list.");
        exit(1);
    }
    List N = newList();
    for(Node A = L->front; A != NULL; A = A->next) {
        append(N, A->data);
    }
    return N;
}

List concatList(List A, List B) {
    if(A == NULL)
    {
        fprintf(stderr, "List error: concatList(List A, List B) - cannot operate on null list A.");
        exit(1);
    }
    else if(B == NULL)
    {
        fprintf(stderr, "List error: concatList(List A, List B) - cannot operate on null list B.");
        exit(1);
    }
    List N = copyList(A);
    for(Node Bnode = B->front; Bnode != NULL; Bnode = Bnode->next) {
        append(N, Bnode->data);
    }
    return N;
}

List uadd(List A, List B){
   List L = newList();
   int i = 0, carry = 0;
   moveFront(A);
   moveFront(B);
   if (length(A) > length(B)){
      for(i = 0; i < length(B); i++){
         append(L, (get(A) + get(B) + carry) % BASE);
         carry = (get(A) + get(B) + carry) / BASE;
         moveNext(A);
         moveNext(B);
      }
      for(; i < length(A); i++){
         append(L, (get(A) + carry) % BASE);
         carry = (get(A) + carry) / BASE;
         moveNext(A);
      }
   } else {
      for(i = 0; i < length(A); i++){
         append(L, (get(A) + get(B) + carry) % BASE);
         carry = (get(A) + get(B) + carry) / BASE;
         moveNext(A);
         moveNext(B);
      }
      for(; i < length(B); i++){
         append(L, (get(B) + carry) % BASE);
         carry = (get(B) + carry) / BASE;
         moveNext(B);
      }
   }
   while(back(L) == 0) {
      deleteBack(L);
   }
   return L;
}

List usub(List A, List B){
   List L = newList();
   int i = 0, carry = 0, j = 0, takeaway = 1;
   moveFront(A);
   moveFront(B);
   for (i = 0; i < length(B); i++) {
      if ((get(A) - carry - get(B)) < 0) {
         takeaway = 1;
         j = get(B) + carry;
         while(j >= 1) {
            j /= 10;
            takeaway *= 10;
         }
         append(L, (get(A) - carry - get(B) + takeaway));
         carry = 1;
         moveNext(A);
         moveNext(B);
      } else {
         append(L, (get(A) - carry - get(B)));
         carry = 0;
         moveNext(A);
         moveNext(B);
      }
   }
   for (; i < length(A); i++) {
      if ((get(A) - carry) < 0) {
         j = carry;
         while(j >= 1) {
            j /= 10;
            takeaway *= 10;
         }
         append(L, (get(A) - carry + takeaway));
         carry = 1;
         moveNext(A);
      } else {
         append(L, (get(A) - carry));
         carry = 0;
         moveNext(A);
      }
   }
   while(back(L) == 0) {
      deleteBack(L);
   }
   return L;
}

List uprod(List A, List B){
   List L = newList();
   int i = 0, j = 0, k = 0;
   unsigned long long int p = 0;
   long carry = 0;
   for (i = 0; i < (length(A) + length(B)); i++){
      append(L, 0);
   }
   for (i = 0; i < length(B); i++){
      carry = 0;
      for (j = 0; j < length(A); j++){
         moveFront(L);
         moveFront(A);
         moveFront(B);
         for (k = 0; k < i + j; k++) {
            moveNext(L);
         }
         for (k = 0; k < j; k++) {
            moveNext(A);
         }
         for (k = 0; k < i; k++) {
            moveNext(B);
         }
         p = (get(L) + (get(A) * get(B)) + carry);
         carry = p / BASE;
         set(L, p % BASE);
         moveFront(L);
         for (k = 0; k < (i + length(A)); k++) {
            moveNext(L);
         }
         set(L, carry);
      }
   }

   while(back(L) == 0) {
      deleteBack(L);
   }
   return L;
}

int compareList(List A, List B){
   int i = 0;
   if (length(A) < length(B)) {
      return -1;
   } else if (length(A) > length(B)) {
      return 1;
   } else {
      moveBack(A);
      moveBack(B);
      for(; i < length(A); i++){
         if(get(A) < get(B)){
            return -1;
         } else if (get(A) > get(B)){
            return 1;
         }
         movePrev(A);
         movePrev(B);
      }
   }
	return 0;
}
