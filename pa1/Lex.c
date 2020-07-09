// Kyle Zhang
// kmzhang
// CSE101
// pa1
// March 31, 2019
// Lex.c
// Description: Source file for a Lex program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

List InsertionSort(char** A, int n){
    int i = 0, j = 0;
	 List L = newList();
	 append(L, 0);
    for (j = 1; j < n; j++) {
		  i = 1;
		  moveFront(L);
		  while (i < length(L) && strcmp(A[j], A[get(L)]) > 0) {
				i++;
		      moveNext(L);
		  }
		  if (strcmp(A[j], A[get(L)]) < 0) {
		      insertBefore(L, j);
		  } else {
			   insertAfter(L, j);
		  }
	 }
	 return L;
}


int main(int argc, char* argv[]) {
    FILE* in;
    FILE* out;
	 List index;
    char* temp = malloc(100*sizeof(char));
    int numline = 0;
    int i = 0;
    if (argc != 3) {
        fprintf(stderr, "Usage: Lex <input file> <output file>\n");
        exit(EXIT_FAILURE);
    }
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    while (fgets(temp, 100, in) != NULL) {
        ++numline;
    }
    fseek(in, 0, SEEK_SET);
    char** strings = calloc(numline, sizeof(char*));
    for (i = 0; i < numline; i++) {
        strings[i] = calloc(100, sizeof(char));
    }
	 i = 0;
    while (i < numline) {
		  fgets(strings[i], 100, in);
        i++;
    }
	 index = InsertionSort(strings, numline);
	 moveFront(index);
	 for (i = 0; i < numline; i++) {
	 	  fprintf(out, "%s", strings[get(index)]);
		  moveNext(index);
    }
	 free(temp);
	 for (i = 0; i < numline; i++) {
		  free(strings[i]);
	 }
	 free(strings);
	 freeList(&index);
	 fclose(in);
	 fclose(out);
    exit(EXIT_SUCCESS);
}
