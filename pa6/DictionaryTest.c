// Kyle Zhang
// kmzhang
// CSE101
// pa6
// May 20, 2020
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
   char* key[] = { "n","z","w","k","i","c","l","d","t","a",
                    "e","y","b","h","v","f","s","m","x","r",
                    "o","u","p","g","j","q" };
   int* value = calloc(26, sizeof(int));
   for (i = 0; i < 26; i++) value[i] = i;
   VAL_TYPE x;
   VAL_TYPE y;

   for(i=0; i<n; i++){
      insert(A, key[i], &value[i]);
   }
   for(i=n-1; i>=0; i--){
      insert(B, key[i], &value[i]);
   }
   printf("%d\n", *lookup(A, "z"));
   printf("%d\n", *lookup(A, "d"));
   printf("%d\n", *lookup(A, "c"));
   printf("forward A:\n");
   for(x=beginForward(A); currentVal(A)!=VAL_UNDEF; x=next(A)){
      printf("key: "KEY_FORMAT" value: %d\n", currentKey(A), *x);
   }
   printf("\n\n");

   printf("reverse B:\n");
   for(y=beginReverse(B); currentVal(B)!=VAL_UNDEF; y=prev(B)){
      printf("key: "KEY_FORMAT" value: %d\n", currentKey(B), *y);
   }
   printf("\n\n");

   printDictionary(stdout, A, "in");
	printf("\n");
   printDictionary(stdout, A, "pre");
	printf("\n");
   printDictionary(stdout, A, "post");
   printf("\n");

   printDictionary(stdout, A, "in");
	printf("\n");
   printDictionary(stdout, A, "pre");
	printf("\n");
   printDictionary(stdout, A, "post");
   printf("\n");

   for(i=0; i<n; i+=2){
      delete(A, key[i]);
   }
   beginForward(A);
   beginReverse(B);
   next(A);
   next(A);
   prev(B);
   prev(B);
   printf("currentKey after next = %s\n", currentKey(A));
   printf("currentVal after next = %d\n", *currentVal(A));
   printf("currentKey after prev = %s\n", currentKey(B));
   printf("currentVal after prev = %d\n", *currentVal(A));

   printDictionary(stdout, A, "in");
	printf("\n");
   printDictionary(stdout, A, "pre");
	printf("\n");
   printDictionary(stdout, A, "post");
   printf("\n");

   for(i=1; i<n; i+=2){
      delete(B, key[i]);
   }

   printDictionary(stdout, A, "in");
	printf("\n");
   printDictionary(stdout, A, "pre");
   printf("\n");
	printDictionary(stdout, A, "post");
   printf("\n");

   for(i=1; i<n; i+=2){
      insert(A, key[i], &value[i]);
   }

   printDictionary(stdout, A, "in");
   printf("\n");
   makeEmpty(A);
   printDictionary(stdout, A, "in");
	printf("\n");
   makeEmpty(B);
   printDictionary(stdout, B, "in");
	printf("\n");
   freeDictionary(&A);
   freeDictionary(&B);
	free(value);
   return(0);
}
