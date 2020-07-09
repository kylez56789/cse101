// Kyle Zhang
// kmzhang
// CSE101
// pa7
// May 30, 2020
//-----------------------------------------------------------------------------
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include"List.h"

using namespace std;

void shuffle(List& D) {
   List A;
   List B;
   int size = D.size();
   int i = 0;
   int j = size/2;
   int k = size - j;
   D.moveFront();
   for (i = 0; i < j; i++) {
      A.insertBefore(D.peekNext());
      D.moveNext();
   }
   for (i = 0; i < k; i++) {
      B.insertBefore(D.peekNext());
      D.moveNext();
   }
   A.moveFront();
   B.moveFront();
   D.moveFront();
   D.clear();
   for (i = 0; i < j; i++) {
      D.insertBefore(B.peekNext());
      B.moveNext();
      D.insertBefore(A.peekNext());
      A.moveNext();
   }
   if (j != k) {
      D.insertBefore(B.peekNext());
   }
}

int main() {
   // shuffle testing
   int n = 1, i = 0, dsize = 1, dmax = 75;
   List X, Y;
   cout << "------------------------------" << endl;
   for (dsize = 1; dsize <= dmax; dsize++) {
      X.insertBefore(dsize);
      Y.insertBefore(dsize);
      shuffle(X);
      while (!(X == Y)) {
         shuffle(X);
         n++;
      }
      cout << " " << dsize << "               " << n << endl;
      n = 1;
   }

   List A, B, C, D, E;

   for(i=1; i<20; i++){
      A.insertAfter(i);
      B.insertAfter(30-i);
      C.insertBefore(i);
      D.insertBefore(30-i);
   }

   cout << endl;
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << endl;

   C.moveFront();
   D.moveFront();

   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;

   cout << endl << "B: ";
   for(i=1; i<=7; i++){
      cout << B.movePrev() << " ";
   }
   cout << endl << "B.position() = " << B.position() << endl;

   cout << endl << "C: ";
   for(i=1; i<=7; i++){
      cout << C.moveNext() << " ";
   }
   cout << endl << "C.position() = " << C.position() << endl;

   cout << endl;
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << endl;

   cout << B.findNext(5) << endl;
   cout << B << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl;
   cout << B.findPrev(2) << endl;
   B.eraseBefore();
   B.eraseAfter();

   for( i=10; i>=1; i--){
      A.insertAfter(i);
      A.movePrev();
   }
   
   cout << "A = " << A << endl;
   for( i=1; i<=15; i++){
      A.moveNext();
   }
   cout << A.position() << endl;
   A.cleanup();
   cout << "A = " << A << endl;
   cout << A.position() << endl;
   cout << endl;

   E = A;
   cout << "E==A is " << (E==A?"true":"false") << endl;
   List F;
   F = A.concat(B);
   A = A;
   cout << endl;

   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << "D = " << D << endl;
   cout << "E = " << E << endl;
   cout << "F = " << F << endl;

   return(0);
}

