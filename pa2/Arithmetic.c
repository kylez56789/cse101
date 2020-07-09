//
// Created by kylez on 4/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"

int main(int argc, char* argv[]){
	FILE* in, *out;
	char sign;
	char newline[100];
   char line1[100];
   char* line2 = "";
   char line3[100];
   char* line4 = "";
   int n = 0;
   if (argc != 3){
      fprintf(stderr, "Usage: Arithmetic <input file> <output file>\n");
      exit(EXIT_FAILURE);
   }
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   fgets(line1, 10, in);
   n = atoi(line1);
   sign = fgetc(in);
   if (sign == '-' || sign == '+') {
      fseek(in, -1, SEEK_CUR);
      line2 = malloc((n + 2) * sizeof(char));
      fgets(line2, n + 2, in);
   } else {
      fseek(in, -1, SEEK_CUR);
      line2 = malloc((n + 1) * sizeof(char));
      fgets(line2, n + 1, in);
   }
   fgets(newline, 2, in);
   BigInteger A = stringToBigInteger(line2);
   fgets(line3, 10, in);
   n = atoi(line3);
   sign = fgetc(in);
   if (sign == '-' || sign == '+') {
      fseek(in, -1, SEEK_CUR);
      line4 = malloc((n + 2) * sizeof(char));
      fgets(line4, n + 2, in);
   } else {
      fseek(in, -1, SEEK_CUR);
      line4 = malloc((n + 1) * sizeof(char));
      fgets(line4, n + 1, in);
   }
   BigInteger B = stringToBigInteger(line4);
   // A
   printBigInteger(out, A);
   fprintf(out, "\n\n");
   // B
   printBigInteger(out, B);
   fprintf(out, "\n\n");
   // A+B
   BigInteger C = sum(A, B);
   printBigInteger(out, C);
   fprintf(out, "\n\n");
   // A-B
   subtract(C, A, B);
   printBigInteger(out, C);
   fprintf(out, "\n\n");
   // A-A
   subtract(C, A, A);
   printBigInteger(out, C);
   fprintf(out, "\n\n");
   BigInteger three = stringToBigInteger("3");
   BigInteger two = stringToBigInteger("2");
   BigInteger nine = stringToBigInteger("9");
   BigInteger sixteen = stringToBigInteger("16");
   // 3A-2B
   BigInteger D = prod(A, three);
   BigInteger E = prod(B, two);
   subtract(C, D, E);
   printBigInteger(out, C);
   fprintf(out, "\n\n");
   // A*B
   multiply(C, A, B);
   printBigInteger(out, C);
   fprintf(out, "\n\n");
   // A^2
   multiply(C, A, A);
   printBigInteger(out, C);
   fprintf(out, "\n\n");
   // B^2
   multiply(C, B, B);
   printBigInteger(out, C);
   fprintf(out, "\n\n");
   // 9A^4 + 16B^5
   BigInteger F = prod(A, A);
   multiply(D, F, F);
   multiply(E, D, nine);
   multiply(F, B, B);
   multiply(D, F, F);
   multiply(F, D, B);
   multiply(D, F, sixteen);
   add(C, D, E);
   printBigInteger(out, C);
	fprintf(out, "\n\n");
   fclose(in);
   fclose(out);
   free(line2);
   free(line4);
   freeBigInteger(&A);
   freeBigInteger(&B);
   freeBigInteger(&C);
   freeBigInteger(&D);
   freeBigInteger(&E);
   freeBigInteger(&F);
	freeBigInteger(&three);
	freeBigInteger(&two);
   freeBigInteger(&nine);
   freeBigInteger(&sixteen);
   return EXIT_SUCCESS;
}
