// Kyle Zhang
// kmzhang
// CSE101
// pa5
// May 15, 2020
// Dictionary.c

#include "Dictionary.h"

typedef struct NodeObj{
    char* key;
    int value;
    struct NodeObj* parent;
    struct NodeObj* left;
    struct NodeObj* right;
} NodeObj;

// Node
typedef NodeObj* Node;

// newNode()
// Constructor for Node type.
Node newNode(char* k, int v) {
   Node N = malloc(sizeof(NodeObj));
   N->key = k;
   N->value = v;
   N->parent = NULL;
   N->left = N->right = NULL;
   return(N);
}

// freeNode()
// Destructor for Node type
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

typedef struct DictionaryObj {
   int unique;
   int numPairs;
   Node cursor;
   Node root;
	Node dummy;
} DictionaryObj;

Dictionary newDictionary(int unique) {
   Dictionary D = malloc(sizeof(DictionaryObj));
   D->root = NULL;
   D->numPairs = 0;
   D->unique = unique;
   D->cursor = NULL;
	D->dummy = newNode(KEY_UNDEF, VAL_UNDEF);
   return D;
}

void freeDictionary(Dictionary* pD) {
   if( pD!=NULL && *pD!=NULL ){
      makeEmpty(*pD);
		free((*pD)->dummy);
      free(*pD);
      *pD = NULL;
   }
}

int size(Dictionary D) {
   return D->numPairs;
}

int getUnique(Dictionary D) {
   return D->unique;
}

Node findKey(Node R, char* k){
   if(R==NULL || KEY_CMP(k, R->key) == 0)
      return R;
   if( KEY_CMP(k, R->key) < 0)
      return findKey(R->left, k);
   else
      return findKey(R->right, k);
}

VAL_TYPE lookup(Dictionary D, KEY_TYPE k) {
   Node N;
   if( D==NULL ){
      fprintf(stderr,
              "Dictionary Error: calling lookup() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }

   N = findKey(D->root, k);
   return (N==NULL ? VAL_UNDEF : N->value);
}

Node findParent(Node N, Node R){
   Node P=NULL;
   if( N!=R ){
      P = R;
      while( P->left!=N && P->right!=N ){
         if(KEY_CMP(N->key, P->key) < 0)
            P = P->left;
         else
            P = P->right;
      }
   }
   return P;
}


void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v) {
   Node N, A, B;
   if( D==NULL ){
      fprintf(stderr,
              "Dictionary Error: calling insert() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   if(D->unique == 1) {
      if( findKey(D->root, k)!=NULL ){
         fprintf(stderr,
                 "Dictionary Error: cannot insert() duplicate key: \"%s\"\n", k);
         exit(EXIT_FAILURE);
      }
   }
   N = newNode(k, v);
   B = NULL;
   A = D->root;
   while( A!=NULL ){
      B = A;
      if( KEY_CMP(k, A->key) < 0 ){
         A = A->left;
      }else{
         A = A->right;
      }
   }
   if( B==NULL ){
      D->root = N;
   }else if( KEY_CMP(k, B->key) < 0 ){
      B->left = N;
   }else{
      B->right = N;
   }
	N->parent = B;
   (D->numPairs)++;
}

Node findLeftmost(Node R){
   Node L = R;
   if( L!=NULL ) for( ; L->left!=NULL; L=L->left) ;
   return L;
}

void delete(Dictionary D, KEY_TYPE k) {
   Node N, P, S;
   if( D==NULL ){
      fprintf(stderr,
              "Dictionary Error: calling delete() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   N = findKey(D->root, k);
   if( N==NULL ){
      fprintf(stderr,
              "Dictionary Error: cannot delete() non-existent key: \"%s\"\n", k);
      exit(EXIT_FAILURE);
   }
   if( N->left==NULL && N->right==NULL ){
      if( N==D->root ){
         D->root = NULL;
         freeNode(&N);
      }else{
         P = findParent(N, D->root);
         if( P->right==N ){
            P->right = NULL;
         }else{
            P->left = NULL;
         }
         freeNode(&N);
      }
   }else if( N->right==NULL ){ 
      if( N==D->root ){
         D->root = N->left;
         freeNode(&N);
      }else{
         P = findParent(N, D->root);
         if( P->right==N ){
            P->right = N->left;
         }else{
            P->left = N->left;
         }
         freeNode(&N);
      }
   }else if( N->left==NULL ){ 
      if( N==D->root ){
         D->root = N->right;
         freeNode(&N);
      }else{
         P = findParent(N, D->root);
         if( P->right==N ){
            P->right = N->right;
         }else{
            P->left = N->right;
         }
         freeNode(&N);
      }
   }else{ 
      S = findLeftmost(N->right);
      N->key = S->key;
      N->value = S->value;
      P = findParent(S, N);
      if( P->right==S ){
         P->right = S->right;
      }else{
         P->left = S->right;
      }
      freeNode(&S);
   }
   (D->numPairs)--;
}

void makeEmpty(Dictionary D) {
   while(D->root != NULL) {
      delete(D, D->root->key);
   }
	D->cursor = D->dummy;
}

Node TreeMinimum(Node x) {
   while (x->left != NULL) {
      x = x->left;
   }
   return x;
}

Node TreeMaximum(Node x) {
   while (x->right != NULL) {
      x = x->right;
   }
   return x;
}

VAL_TYPE beginForward(Dictionary D) {
	D->cursor = D->root;
	if (D->numPairs == 0) {
		return VAL_UNDEF;
	}
   D->cursor = TreeMinimum(D->cursor);
	return currentVal(D);
}

VAL_TYPE beginReverse(Dictionary D) {
	D->cursor = D->root;
	if (D->numPairs == 0) {
      return VAL_UNDEF;
   }
   D->cursor = TreeMaximum(D->cursor);
   return currentVal(D);
}

KEY_TYPE currentKey(Dictionary D) {
   if (D->cursor == NULL) {
      return KEY_UNDEF;
   } else {
      return D->cursor->key;
   }
}

VAL_TYPE currentVal(Dictionary D) {
   if (D->cursor == NULL) {
      return VAL_UNDEF;
   } else {
      return D->cursor->value;
   }
}

Node TreeSuccessor(Node x) {
   if (x->right != NULL) {
      return TreeMinimum(x->right);
   }
   Node y = x->parent;
   while (y != NULL && x == y->right) {
      x = y;
      y = y->parent;
   }
   return y;
}

Node TreePredecessor(Node x) {
   if (x->left != NULL) {
      return TreeMaximum(x->left);
   }
   Node y = x->parent;
   while (y != NULL && x == y->left) {
      x = y;
      y = y->parent;
   }
   return y;
}

VAL_TYPE next(Dictionary D) {
   D->cursor = TreeSuccessor(D->cursor);
   if (D->cursor == NULL) {
      D->cursor = D->dummy;
   }
   return currentVal(D);
}

VAL_TYPE prev(Dictionary D) {
   D->cursor = TreePredecessor(D->cursor);
   if (D->cursor == NULL) {
      D->cursor = D->dummy;
   }
   return currentVal(D);
}

void printDict(FILE* out, Node R) {
   if (R != NULL) {
      printDict(out, R->left);
      fprintf(out, "%s\n", R->key);
      printDict(out, R->right);
   }
}

Node TreeMax(Dictionary D) {
   Node M = D->root;
   while (M->right != NULL) {
      M = M->right;
   }
   return M;
}

void printDictionary(FILE* out, Dictionary D) {
   Node R = D->root;
   printDict(out, R);
}
