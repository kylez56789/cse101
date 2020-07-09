// Kyle Zhang
// kmzhang
// CSE101
// pa4
// May 1, 2020
// List.c
// Description: Source file for a List ADT

#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BASE 1000000000
#define POWER 9

typedef struct NodeObj {
   int data;
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

Node newNode(int data) {
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

int front(List L) {
    if(L == NULL) {
        fprintf(stderr, "List error: front(List L) - cannot operate on a null list.");
        exit(1);
    } else {
        return L->front->data;
    }
}

int back(List L) {
    if(L == NULL)
    {
        fprintf(stderr, "List error: back(List L) - cannot operate on a null list.");
        exit(1);
    } else {
        return L->back->data;
    }
}

int get(List L) {
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

int equals(List A, List B){
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

void prepend(List L, int data) {
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

void append(List L, int data) {
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

void insertBefore(List L, int data) {
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

void insertAfter(List L, int data) {
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

void set(List L, int x){
    if(L == NULL) {
        fprintf(stderr, "List error: set(List L, int x) - cannot operate on a null list.");
        exit(1);
    } else if (L->curindex == -1){
        fprintf (stderr, "List error: set(List L, int x) - cursor undefined.");
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
            fprintf(out, "%d", A->data);
            first = 0;
        } else {
            fprintf(out, " %d", A->data);
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
