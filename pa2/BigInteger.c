//  Kyle Zhang
//  kmzhang
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "BigInteger.h"

#define POWER 9
#define BASE 1000000000

typedef struct NodeObj {
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;

typedef struct BigIntegerObj{
    int sign;
    List L;
} BigIntegerObj;

BigInteger newBigInteger(){
    BigInteger B = malloc(sizeof(BigIntegerObj));
    B->L = newList();
    int sign = 0;
    return B;
}

void freeBigInteger(BigInteger* pN){
    if (*pN != NULL && pN != NULL) {
        freeList(&((*pN)->L));
        free(*pN);
        *pN = NULL;
    }
}

int sign(BigInteger N){
    return N->sign;
}

int compare(BigInteger A, BigInteger B){
    if (equals(A, B)){
       return 0;
    } else if (A->sign != B->sign) {
       return A->sign == -1 ? -1 : 1;
    } else {
       return compareList(A->L, B->L);
    }
}

int equals(BigInteger A, BigInteger B){
   if (A->sign != B->sign){
      return 0;
   } else if (!listEquals(A->L, B->L)){
      return 0;
   } else {
      return 1;
   }
}

void makeZero(BigInteger N){
   clear(N->L);
   N->sign = 0;
}

void negate(BigInteger N){
   N->sign *= -1;
}

BigInteger stringToBigInteger(char* s){
   BigInteger B = newBigInteger();
   if(s[0] == '0' && strlen(s) == 1) {
      return B;
   }
   int segs = 0, j = 0, k = 0, a = 0, b = 0;
   long i = strlen(s), ret = 0;
   if (s[0] == '-') {
      B->sign = -1;
      i -= 1;
      j = 1;
      while (s[j] == '0') {
         i--;
         j++;
      }
   } else if (s[0] == '+'){
      B->sign = 1;
      j = 1;
      while (s[j] == '0') {
         i--;
         j++;
      }
   } else {
      B->sign = 1;
      j = 0;
      while (s[j] == '0') {
         i--;
         j++;
      }
   }
   if (i % POWER == 0) {
      segs = i / POWER;
   } else {
      segs = (i / POWER) + 1;
   }
   char* ptr = NULL;
   char** segments = malloc(segs*sizeof(char*));
   for(i = 0; i < segs; i++){
      segments[i] = malloc((POWER+1)*sizeof(char));
   }
   if(s[0] == '-') {
      i = 1;
      while (s[j] == '0') {
         i++;
      }
   } else if (s[0] == '+'){
		i = 1;
      while (s[j] == '0') {
         i++;
      }
   } else {
      i = 0;
      while (s[j] == '0') {
         i++;
      }
   }
   for(j = 1; j <= segs; j++){
      a = strlen(s);
      a -= j * POWER;
      b = a + 9;
      while (a < i) {
         a++;
      }
      for(k = 0; k < POWER && a < b; k++, a++) {
         segments[j-1][k] = s[a];
      }
		segments[j-1][k] = '\0';
   }
   for(i = 0; i < segs; i++) {
      ret = strtol(segments[i], &ptr, 10);
      append(B->L, ret);
   }
   for(i = 0; i < segs; i++) {
      free(segments[i]);
   }
   free(segments);
   return B;
}

BigInteger copy(BigInteger N){
   BigInteger B = newBigInteger();
   B->sign = N->sign;
	freeList(&(B->L));
   B->L = copyList(N->L);
   return B;
}

void add(BigInteger S, BigInteger A, BigInteger B) {
   if (A->sign == B->sign){
      freeList(&(S->L));
      S->L = uadd(A->L, B->L);
      S->sign = A->sign;
   } else if (listEquals(A->L, B->L)) {
      makeZero(S);
   } else if (compareList(A->L, B->L) == -1) {
      freeList(&(S->L));
      S->L = usub(B->L, A->L);
      S->sign = B->sign;
   } else {
      freeList(&(S->L));
      S->L = usub(A->L, B->L);
      S->sign = A->sign;
   }
}

BigInteger sum(BigInteger A, BigInteger B){
   BigInteger S = newBigInteger();
   if (A->sign == B->sign){
      freeList(&(S->L));
      S->L = uadd(A->L, B->L);
      S->sign = A->sign;
   } else if (listEquals(A->L, B->L)) {
      makeZero(S);
   } else if (compareList(A->L, B->L) == -1) {
      freeList(&(S->L));
      S->L = usub(B->L, A->L);
      S->sign = B->sign;
   } else {
      freeList(&(S->L));
      S->L = usub(A->L, B->L);
      S->sign = A->sign;
   }
   return S;
}

void subtract(BigInteger D, BigInteger A, BigInteger B){
   if (A->sign != B->sign) {
      freeList(&(D->L));
      D->L = uadd(A->L, B->L);
      D->sign = A->sign;
   } else if (equals(A, B)) {
      makeZero(D);
   } else if (compare(A, B) == -1) {
      freeList(&(D->L));
      D->L = usub(B->L, A->L);
      D->sign = B->sign * -1;
   } else {
      freeList(&(D->L));
      D->L = usub(A->L, B->L);
      D->sign = A->sign;
   }
}

BigInteger diff(BigInteger A, BigInteger B){
   BigInteger D = newBigInteger();
   if (A->sign != B->sign) {
      freeList(&(D->L));
      D->L = uadd(A->L, B->L);
      D->sign = A->sign;
   } else if (equals(A, B)) {
      makeZero(D);
   } else if (compare(A, B) == -1) {
      freeList(&(D->L));
      D->L = usub(B->L, A->L);
      D->sign = B->sign * -1;
   } else {
      freeList(&(D->L));
      D->L = usub(A->L, B->L);
      D->sign = A->sign;
   }
   return D;
}

void multiply(BigInteger P, BigInteger A, BigInteger B){
   freeList(&(P->L));
   if (A == B) {
      List C = copyList(A->L);
      P->L = uprod(A->L, C);
      freeList(&C);
   } else {
      P->L = uprod(A->L, B->L);
   }
   P->sign = A->sign * B->sign;
}

BigInteger prod(BigInteger A, BigInteger B){
   BigInteger P = newBigInteger();
	freeList(&(P->L));
	if (A == B) {
      List C = copyList(A->L);
      P->L = uprod(A->L, C);
      freeList(&C);
   } else {
      P->L = uprod(A->L, B->L);
   }
   P->sign = A->sign * B->sign;
	return P;
}

void printBigInteger(FILE* out, BigInteger N){
   if (length(N->L) == 0 && N->sign == 0){
      fprintf(out, "0");
   }
   if (N->sign == -1) {
      fprintf(out, "-");
   }
   moveBack(N->L);
   while(index(N->L) >= 0) {
      if (index(N->L) != length(N->L) - 1) {
         fprintf(out, "%0*ld", POWER, get(N->L));
         movePrev(N->L);
      } else {
         fprintf(out, "%ld", get(N->L));
         movePrev(N->L);
      }
   }
}
