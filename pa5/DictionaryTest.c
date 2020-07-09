// Kyle Zhang
// kmzhang
// CSE101
// pa5
// May 15, 2020
//-----------------------------------------------------------------------------
// DictionaryTest.c
// Test client for Dictionary ADT
//-----------------------------------------------------------------------------

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Dictionary.h"

int main(int argc, char* argv[]){
   int i, n=26;
   Dictionary A = newDictionary(0);
   Dictionary B = newDictionary(1);
   char* word[] = { "n","z","w","k","i","c","l","d","t","a",
                    "e","y","b","h","v","f","s","m","x","r",
                    "o","u","p","g","j","q" };
   VAL_TYPE x;
   VAL_TYPE y;

   for(i=0; i<n; i++){
      insert(A, word[i], i);
   }
   for(i=n-1; i>=0; i--){
      insert(B, word[i], i);
   }
   printf("%d\n", lookup(A, "z"));
   printf("%d\n", lookup(A, "d"));
   printf("%d\n", lookup(A, "c"));
   printf("forward A:\n");
   for(x=beginForward(A); currentVal(A)!=VAL_UNDEF; x=next(A)){
      printf("key: "KEY_FORMAT" value: "VAL_FORMAT"\n", currentKey(A), x);
   }
   printf("\n\n");

   printf("reverse B:\n");
   for(y=beginReverse(B); currentVal(B)!=VAL_UNDEF; y=prev(B)){
      printf("key: "KEY_FORMAT" value: "VAL_FORMAT"\n", currentKey(B), y);
   }
   printf("\n\n");

   printDictionary(stdout, A);
   printf("\n");

   printDictionary(stdout, B);
   printf("\n");

   for(i=0; i<n; i+=2){
      delete(A, word[i]);
   }
   beginForward(A);
   beginReverse(B);
   next(A);
   next(A);
   prev(B);
   prev(B);
   printf("currentKey after next = %s\n", currentKey(A));
   printf("currentVal after next = %d\n", currentVal(A));
   printf("currentKey after prev = %s\n", currentKey(B));
   printf("currentVal after prev = %d\n", currentVal(A));

   printDictionary(stdout, A);
   printf("\n");

   for(i=1; i<n; i+=2){
      delete(B, word[i]);
   }

   printDictionary(stdout, B);
   printf("\n");

   for(i=1; i<n; i+=2){
      insert(A, word[i], i);
   }

   printDictionary(stdout, A);
   printf("\n");
   makeEmpty(A);
   printDictionary(stdout, A);
   makeEmpty(B);
   printDictionary(stdout, B);
   freeDictionary(&A);
   freeDictionary(&B);
   return(0);
}
