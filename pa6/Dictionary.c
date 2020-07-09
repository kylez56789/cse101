// Kyle Zhang
// kmzhang
// CSE101
// pa6
// May 20, 2020
// Dictionary.c

#include "Dictionary.h"
#define BLACK 1
#define RED 2


typedef struct NodeObj{
    char* key;
    int* value;
    int color;
    struct NodeObj* parent;
    struct NodeObj* left;
    struct NodeObj* right;
} NodeObj;

// Node
typedef NodeObj* Node;

// newNode()
// Constructor for Node type.
Node newNode(char* k, int *v) {
   Node N = malloc(sizeof(NodeObj));
   N->key = k;
   N->value = v;
   N->parent = NULL;
   N->left = N->right = NULL;
   N->color = BLACK;
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
   D->numPairs = 0;
   D->unique = unique;
   D->cursor = NULL;
	D->dummy = newNode(KEY_UNDEF, VAL_UNDEF);
   D->root = D->dummy;
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

Node findKey(Dictionary D, Node R, char* k){
   if(R==D->dummy || KEY_CMP(k, R->key) == 0)
      return R;
   if( KEY_CMP(k, R->key) < 0)
      return findKey(D, R->left, k);
   else
      return findKey(D, R->right, k);
}

VAL_TYPE lookup(Dictionary D, KEY_TYPE k) {
   Node N;
   if( D==NULL ){
      fprintf(stderr,
              "Dictionary Error: calling lookup() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }

   N = findKey(D, D->root, k);
   return (N==D->dummy ? VAL_UNDEF : N->value);
}


Node TreeMinimum(Dictionary D, Node x) {
   while (x->left != D->dummy) {
      x = x->left;
   }
   return x;
}

Node TreeMaximum(Dictionary D, Node x) {
   while (x->right != D->dummy) {
      x = x->right;
   }
   return x;
}

void LeftRotate(Dictionary D, Node x) {
   Node y = x->right;
   x->right = y->left;
   if (y->left != D->dummy) {
      y->left->parent = x;
   }
   y->parent = x->parent;
   if (x->parent == D->dummy) {
      D->root = y;
   } else if (x == x->parent->left) {
      x->parent->left = y;
   } else {
      x->parent->right = y;
   }
   y->left = x;
   x->parent = y;
}

void RightRotate(Dictionary D, Node x) {
   Node y = x->left;
   x->left = y->right;
   if (y->right != D->dummy) {
      y->right->parent = x;
   }
   y->parent = x->parent;
   if (x->parent == D->dummy) {
      D->root = y;
   } else if (x == x->parent->right) {
      x->parent->right = y;
   } else {
      x->parent->left = y;
   }
   y->right = x;
   x->parent = y;
}

void RB_Transplant(Dictionary D, Node u, Node v) {
   if (u->parent == D->dummy) {
      D->root = v;
   } else if (u == u->parent->left) {
      u->parent->left = v;
   } else {
      u->parent->right = v;
   }
   v->parent = u->parent;
}

void RB_InsertFixUp(Dictionary D, Node z) {
   Node y = D->dummy;
   while (z->parent->color == RED) {
      if (z->parent == z->parent->parent->left) {
         y = z->parent->parent->right;
         if (y->color == RED) {
            z->parent->color = BLACK;
            y->color = BLACK;
            z->parent->parent->color = RED;
            z = z->parent->parent;
         } else {
            if (z == z->parent->right) {
               z = z->parent;
               LeftRotate(D, z);
            }
            z->parent->color = BLACK;
            z->parent->parent->color = RED;
            RightRotate(D, z->parent->parent);
         }
      } else {
         y = z->parent->parent->left;
         if (y->color == RED) {
            z->parent->color = BLACK;
            y->color = BLACK;
            z->parent->parent->color = RED;
            z = z->parent->parent;
         } else {
            if (z == z->parent->left) {
               z = z->parent;
               RightRotate(D, z);
            }
            z->parent->color = BLACK;
            z->parent->parent->color = RED;
            LeftRotate(D, z->parent->parent);
         }
      }
   }
   D->root->color = BLACK;
}

void RB_Insert(Dictionary D, Node z) {
   Node y = D->dummy;
   Node x = D->root;
   while (x != D->dummy) {
      y = x;
      if (KEY_CMP(z->key, x->key) < 0) {
         x = x->left;
      } else {
         x = x->right;
      }
   }
   z->parent = y;
   if (y == D->dummy) {
      D->root = z;
   } else if (KEY_CMP(z->key, y->key) < 0) {
      y->left = z;
   } else {
      y->right = z;
   }
   z->left = D->dummy;
   z->right = D->dummy;
   z->color = RED;
   RB_InsertFixUp(D, z);
}

void RB_DeleteFixUp(Dictionary D, Node x) {
   Node w = D->dummy;
   while (x != D->root && x->color == BLACK) {
      if (x == x->parent->left) {
         w = x->parent->right;
         if (w->color == RED) {
            w->color = BLACK;
            x->parent->color = RED;
            LeftRotate(D, x->parent);
            w = x->parent->right;
         }
         if (w->left->color == BLACK && w->right->color == BLACK) {
            w->color = RED;
            x = x->parent;
         } else {
            if (w->right->color == BLACK) {
               w->left->color = BLACK;
               w->color = RED;
               RightRotate(D, w);
               w = x->parent->right;
            }
            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->right->color = BLACK;
            LeftRotate(D, x->parent);
            x = D->root;
         }
      } else {
         w = x->parent->left;
         if (w->color == RED) {
            w->color = BLACK;
            x->parent->color = RED;
            RightRotate(D, x->parent);
            w = x->parent->left;
         }
         if (w->right->color == BLACK && w->left->color == BLACK) {
            w->color = RED;
            x = x->parent;
         } else {
            if (w->left->color == BLACK) {
               w->right->color = BLACK;
               w->color = RED;
               LeftRotate(D, w);
               w = x->parent->left;
            }
            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->left->color = BLACK;
            RightRotate(D, x->parent);
            x = D->root;
         }
      }
   }
   x->color = BLACK;
}

void RB_Delete(Dictionary D, Node z) {
   Node y = z;
   Node x = D->dummy;
   int ycolor = y->color;
   if (z->left == D->dummy) {
      x = z->right;
      RB_Transplant(D, z, z->right);
   } else if (z->right == D->dummy) {
      x = z->left;
      RB_Transplant(D, z, z->left);
   } else {
      y = TreeMinimum(D, z->right);
      ycolor = y->color;
      x = y->right;
      if (y->parent == z) {
         x->parent = y;
      } else {
         RB_Transplant(D, y, y->right);
         y->right = z->right;
         y->right->parent = y;
      }
      RB_Transplant(D, z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
   }
   if (ycolor == BLACK) {
      RB_DeleteFixUp(D, x);
   }
}

void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v) {
   if (D->unique == 1 && lookup(D, k) != VAL_UNDEF) {
      fprintf(stderr, "Dictionary Error: Inserting Duplicate Key Into Unique Dictionary\n");
      exit(EXIT_FAILURE);
   }
   Node z = newNode(k, v);
   RB_Insert(D, z);
   (D->numPairs)++;
}

void delete(Dictionary D, KEY_TYPE k) {
   Node z = findKey(D, D->root, k);
	if (D->cursor == z) {
		D->cursor = NULL;
	}
   RB_Delete(D, z);
   freeNode(&z);
   (D->numPairs)--;
}

void makeEmpty(Dictionary D) {
   while(D->root != D->dummy) {
      delete(D, D->root->key);
   }
	D->cursor = D->dummy;
}

VAL_TYPE beginForward(Dictionary D) {
	D->cursor = D->root;
	if (D->numPairs == 0) {
		return VAL_UNDEF;
	}
   D->cursor = TreeMinimum(D, D->cursor);
	return currentVal(D);
}

VAL_TYPE beginReverse(Dictionary D) {
	D->cursor = D->root;
	if (D->numPairs == 0) {
      return VAL_UNDEF;
   }
   D->cursor = TreeMaximum(D, D->cursor);
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

Node TreeSuccessor(Dictionary D, Node x) {
   if (x->right != D->dummy) {
      return TreeMinimum(D, x->right);
   }
   Node y = x->parent;
   while (y != NULL && x == y->right) {
      x = y;
      y = y->parent;
   }
   return y;
}

Node TreePredecessor(Dictionary D, Node x) {
   if (x->left != D->dummy) {
      return TreeMaximum(D, x->left);
   }
   Node y = x->parent;
   while (y != D->dummy && x == y->left) {
      x = y;
      y = y->parent;
   }
   return y;
}

VAL_TYPE next(Dictionary D) {
   D->cursor = TreeSuccessor(D, D->cursor);
   if (D->cursor == NULL) {
      D->cursor = D->dummy;
   }
   return currentVal(D);
}

VAL_TYPE prev(Dictionary D) {
   D->cursor = TreePredecessor(D, D->cursor);
   if (D->cursor == NULL) {
      D->cursor = D->dummy;
   }
   return currentVal(D);
}

void printDict(FILE* out, Node N, const char* ord) {
   if (N->left != NULL && N->right != NULL) {
      if (strcmp(ord, "pre") == 0) {
         fprintf(out, "%s", N->key);
         printDict(out, N->left, ord);
         printDict(out, N->right, ord);
      } else if (strcmp(ord, "in") == 0) {
         printDict(out, N->left, ord);
         fprintf(out, "%s", N->key);
         printDict(out, N->right, ord);
      } else if (strcmp(ord, "post") == 0) {
         printDict(out, N->left, ord);
         printDict(out, N->right, ord);
         fprintf(out, "%s", N->key);
      }
   }
}

void printDictionary(FILE* out, Dictionary D, const char* ord) {
   if (strcmp(ord, "pre") == 0) {
      fprintf(out, "******************************************************\n");
      fprintf(out, "PRE-ORDER:\n");
      fprintf(out, "******************************************************\n");
      printDict(out, D->root, ord);
   } else if (strcmp(ord, "in") == 0) {
      fprintf(out, "******************************************************\n");
      fprintf(out, "IN-ORDER:\n");
      fprintf(out, "******************************************************\n");
      printDict(out, D->root, ord);
   } else if (strcmp(ord, "post") == 0) {
      fprintf(out, "******************************************************\n");
      fprintf(out, "POST-ORDER:\n");
      fprintf(out, "******************************************************\n");
      printDict(out, D->root, ord);
   }
}
