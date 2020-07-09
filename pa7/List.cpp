// Kyle Zhang
// kmzhang
// CSE101
// pa7
// May 30, 2020

#include "List.h"

using namespace std;

#define MIN -2147483648
#define MAX 2147483647

List::Node::Node(int x){
   data = x;
   next = nullptr;
   prev = nullptr;
}

List::List() {
   Node* A = new Node(MIN);
   Node* B = new Node(MAX);
   A->next = B;
   B->prev = A;
   frontDummy = A;
   backDummy = B;
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = A;
   afterCursor = B;
   pos_cursor = 0;
   num_elements = 0;
}

List::List(const List& L) {
   Node* A = new Node(0);
   Node* B = new Node(0);
   A->next = B;
   B->prev = A;
   frontDummy = A;
   backDummy = B;
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = A;
   afterCursor = B;
   pos_cursor = 0;
   num_elements = 0;
   Node* N = L.frontDummy->next;
   while(N != L.backDummy) {
      this->insertAfter(N->data);
      N = N->next;
   }
}

List::~List() {
   clear();
	delete(frontDummy);
	delete(backDummy);
}

bool List::isEmpty() {
   return (num_elements==0);
}

int List::size() {
   return num_elements;
}

int List::position() {
   return pos_cursor;
}

void List::moveFront() {
   pos_cursor = 0;
   afterCursor = frontDummy->next;
   beforeCursor = frontDummy;
}

void List::moveBack() {
   pos_cursor = size();
   beforeCursor = backDummy->prev;
   afterCursor = backDummy;
}

int List::peekNext() {
   return afterCursor->data;
}

int List::peekPrev() {
   return beforeCursor->data;
}

int List::moveNext() {
   beforeCursor = beforeCursor->next;
   afterCursor = afterCursor->next;
   ++pos_cursor;
   return beforeCursor->data;
}

int List::movePrev() {
   afterCursor = afterCursor->prev;
   beforeCursor = beforeCursor->prev;
   --pos_cursor;
   return afterCursor->data;
}

void List::insertAfter(int x) {
   Node* N = new Node(x);
   N->prev = beforeCursor;
   N->next = afterCursor;
   beforeCursor->next = N;
   afterCursor->prev = N;
   afterCursor = N;
   ++num_elements;
}

void List::insertBefore(int x) {
   Node* N = new Node(x);
   N->prev = beforeCursor;
   N->next = afterCursor;
   beforeCursor->next = N;
   afterCursor->prev = N;
   beforeCursor = N;
   ++pos_cursor;
   ++num_elements;
}

void List::eraseAfter() {
   Node* N = afterCursor;
   beforeCursor->next = afterCursor->next;
   afterCursor->next->prev = beforeCursor;
   afterCursor = afterCursor->next;
   delete N;
   --num_elements;
}

void List::eraseBefore() {
   Node* N = beforeCursor;
   afterCursor->prev = beforeCursor->prev;
   beforeCursor->prev->next = afterCursor;
   beforeCursor = beforeCursor->prev;
   delete N;
   --pos_cursor;
   --num_elements;
}

int List::findNext(int x) {
   moveNext();
   while (pos_cursor <= size()) {
      if (beforeCursor->data == x) {
         return pos_cursor;
      } else if (pos_cursor == size()){
         break;
      }
      moveNext();
   }
	pos_cursor = size();
   return -1;
}

int List::findPrev(int x) {
   movePrev();
   while (pos_cursor >= 0) {
      if (afterCursor->data == x) {
         return pos_cursor;
      } else if (pos_cursor == 0){
         break;
      }
      movePrev();
   }
	pos_cursor = 0;
   return -1;
}

void List::cleanup() {
   Node* N = frontDummy->next;
   int i = 0, j = 0;
   int k = pos_cursor;
   while (N != backDummy) {
      moveFront();
      findNext(N->data);
      while (true) {
         if (N->next == backDummy) {
            break;
         }
         i = findNext(N->data);
         if (i == -1) {
            break;
         }
         if (pos_cursor <= k) {
            k--;
         }
         eraseBefore();
      }
      N = frontDummy->next;
      j++;
      for (i = 0; i < j; i++) {
         N = N->next;
      }
   }
	moveFront();
	for (i = 0; i < k; i++) {
		moveNext();
	}
}

void List::clear() {
   moveFront();
   while (num_elements > 0) {
      eraseAfter();
   }
}

List List::concat(const List& L) {
   List A;
   Node* N = frontDummy->next;
   while (N != backDummy) {
      A.insertBefore(N->data);
      N = N->next;
   }
   N = L.frontDummy->next;
   while (N != L.backDummy) {
      A.insertBefore(N->data);
      N = N->next;
   }
   return A;
}

string List::to_string() {
   Node* N = nullptr;
   string s = "(";
   for(N=frontDummy->next; N!=backDummy->prev; N=N->next){
      s += std::to_string(N->data)+", ";
   }
   s += std::to_string(N->data);
   s += ")";
   return s;
}

bool List::equals(const List& R) {
   bool eq = false;
   Node* N = nullptr;
   Node* M = nullptr;
   eq = ( this->num_elements == R.num_elements);
   N = this->frontDummy;
   M = R.frontDummy;
   while( eq && N!=backDummy){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}

ostream& operator<< (ostream& stream, List& L) {
   return stream << L.List::to_string();
}

bool operator==( List& A, const List& B ) {
   return A.List::equals(B);
}

List& List::operator=( const List& L ) {
   if(this != &L) {
      this->clear();
      Node* N = L.frontDummy->next;
      while (N != L.backDummy) {
         insertBefore(N->data);
         N = N->next;
      }
      moveFront();
   }
   return *this;
}
