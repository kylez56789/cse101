// Kyle Zhang
// kmzhang
// CSE101
// pa5
// May 15, 2020
// Lex.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

int main(int argc, char* argv[]) {
   FILE* in;
   FILE* out;
   char* temp = malloc(100*sizeof(char));
   int numline = 0;
   int i = 0;
   if (argc != 3) {
      fprintf(stderr, "Usage: Lex <input file> <output file>\n");
      exit(EXIT_FAILURE);
   }
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   while (fgets(temp, 160, in) != NULL) {
      ++numline;
   }
   fseek(in, 0, SEEK_SET);
   char** strings = calloc(numline, sizeof(char*));
   for (i = 0; i < numline; i++) {
      strings[i] = calloc(160, sizeof(char));
   }
   i = 0;
   while (i < numline) {
      fgets(strings[i], 160, in);
      i++;
   }
   Dictionary D = newDictionary(0);
   for (i = 0; i < numline; i++) {
      insert(D, strings[i], VAL_UNDEF);
   }
   printDictionary(out, D);
   free(temp);
   for (i = 0; i < numline; i++) {
      free(strings[i]);
   }
   free(strings);
   freeDictionary(&D);
   fclose(in);
   fclose(out);
   exit(EXIT_SUCCESS);
}
