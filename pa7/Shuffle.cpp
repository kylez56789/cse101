// Kyle Zhang
// kmzhang
// CSE101
// pa7
// May 30, 2020

#include <iostream>
#include <string>
#include "List.h"

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

int main(int argc, char * argv[]) {
   int n = 1, dsize = 1;
   if (argc != 2) {
      cerr << "Usage:" << argv[0] << "<integer>" << endl;
      return (EXIT_FAILURE);
   }
   List D, B;
   int dmax = atoi(argv[1]);
	cout << "deck size       shuffle count" << endl;
   cout << "------------------------------" << endl;
   for (dsize = 1; dsize <= dmax; dsize++) {
      D.insertBefore(dsize);
      B.insertBefore(dsize);
      shuffle(D);
      while (!(D == B)) {
         shuffle(D);
         n++;
      }
      cout << " " << dsize << "               " << n << endl;
      n = 1;
   }
   return(0);
}
