//
// Created by kylez on 4/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"

int main(int argc, char* argv[]){
   BigInteger A = stringToBigInteger("9163574346363325007361058");
   BigInteger B = stringToBigInteger("+4597814412658653960738664");
   printBigInteger(stdout, A);
   fprintf(stdout, "\n\n");
   printBigInteger(stdout, B);
   fprintf(stdout, "\n\n");
   BigInteger C = sum(A, B);
   printBigInteger(stdout, C);
   fprintf(stdout, "\n\n");
   subtract(C, A, B);
   printBigInteger(stdout, C);
   fprintf(stdout, "\n\n");
   subtract(C, A, A);
   printBigInteger(stdout, C);
   fprintf(stdout, "\n\n");
   BigInteger three = stringToBigInteger("3");
   BigInteger two = stringToBigInteger("2");
   BigInteger nine = stringToBigInteger("9");
   BigInteger sixteen = stringToBigInteger("16");

   BigInteger D = prod(A, three);
   BigInteger E = prod(B, B);
   subtract(C, D, E);
   printBigInteger(stdout, C);
   fprintf(stdout, "\n\n");
   multiply(C, A, A);
   printBigInteger(stdout, C);
   fprintf(stdout, "\n\n");
   multiply(C, A, D);
   printBigInteger(stdout, C);
   fprintf(stdout, "\n\n");
   multiply(C, B, E);
   printBigInteger(stdout, C);
   fprintf(stdout, "\n\n");
   freeBigInteger(&A);
   freeBigInteger(&B);
	freeBigInteger(&C);
	freeBigInteger(&D);
   freeBigInteger(&E);
	freeBigInteger(&three);
   freeBigInteger(&two);
   freeBigInteger(&nine);
   freeBigInteger(&sixteen);
   return EXIT_SUCCESS;
}
