/*------------------------------------------------
File Name: List.c
Name:   Joseph Csoti
CruzID: 1617438 // jcsoti
Class:  CMPS 101
Date:   10/22/18
------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "List.h"

// private types --------------------------------

// NodeObj
typedef struct NodeObj{
  int* item;
  struct NodeObj* next;
  struct NodeObj* prev;
} NodeObj;

// newNode()
// constructor of the Node type
Node newNode(int* item) {
  Node N = malloc(sizeof(NodeObj));
  assert(N!=NULL);
  N->item = item;
  N->prev = NULL;
  N->next = NULL;
  return(N);
}

// freeNode()
// destructor for the Node type
void freeNode(Node pN){
  if(pN != NULL) {
    free(pN);
    pN = NULL;
  }
}
// ------------------------------------

//Listobj
typedef struct ListObj {
  struct NodeObj* head;
  struct NodeObj* tail;
  struct NodeObj* cursor;
} ListObj;

// Constructors-Destructors ---------------------------------------------------
List newList(void) {
  List L = malloc(sizeof(ListObj));
  assert(L!=NULL);
  return L;
}

void freeList(List* pL) {
  if( pL!=NULL && *pL!=NULL ){
    free(*pL);
    *pL = NULL;
 }
}

// Access functions -----------------------------------------------------------
int length(List L) {

  if(L->head == NULL)
    return 0;
  if(L->head == L->tail)
    return 1;

  int len = 0;
  Node cur = L->head;

  while(cur != NULL) {
    len++;
    cur = cur->next;
  }

  return len;
}

int index(List L) {
  if(L->cursor == NULL)
    return -1;

  int index = 0;
  Node cur = L->head;

  while(cur != NULL){
    if(L->cursor == cur)
      return index;
    
    cur = cur->next;
    index++;
  }

  return index;
}

int front(List L) {
  if(length(L) <= 0) {
    fprintf(stderr, "List.c: front() called on an empty list\n");
    exit(1);
  }
  return *(L->head->item);
}

int back(List L) {
  if(length(L) <= 0) {
    fprintf(stderr, "List.c: back() called on an empty list\n");
    exit(1);
  }
  return *(L->tail->item);
}

int get(List L) {
  if(length(L) <= 0) {
    fprintf(stderr, "List.c: get() called on an empty list\n");
    exit(1);
  }
  if(index(L) < 0) {
    fprintf(stderr, "List.c: get() invalid index\n");
    exit(1);
  }
  return *(L->cursor->item);
}

int equals(List A, List B) {
  // check size
  if (length(A) == length(B)) {
    Node cur_a = A->head;
    Node cur_b = B->head;
    // check items
    while (cur_a != NULL || cur_b != NULL) {
      if (cur_a->item != cur_b->item)
        return 0; // Value @ curr is different
      cur_a = cur_a->next;
      cur_b = cur_b->next;
    }
      return 1; // All items are equal
    } else return 0; // Size is diff

    return 0;
}

// Manipulation procedures ----------------------------------------------------
void clear(List L) {

Node curr = L->head;
while( curr != NULL ) {
   Node next = curr->next;
   free(curr->item)
   free(curr);
   curr = next;
}
  //freeNode(L->cursor);
}
void moveFront(List L) {
  if(length(L) > 0)
    L->cursor = L->head;
}
void moveBack(List L){
  if(length(L) > 0)
    L->cursor = L->tail;
}
void movePrev(List L){
  if(L->cursor == NULL)
    return;
  
  if (L->cursor == L->head) {
    freeNode(L->cursor);
    return;
  }

  if (L->cursor != L->head) {
    L->cursor = L->cursor->prev;
    return;
  }
}
void moveNext(List L) {
  if (L->cursor == NULL)
    return;

  if (L->cursor == L->tail) {
    freeNode(L->cursor);
    return;
  }

  if (L->cursor != L->tail) {
    L->cursor = L->cursor->next;
    return;
  }
}
void prepend(List L, int data){
    Node node = newNode(&data);

    // First node
    if (L->head == NULL) {
      L->head = node;
      L->tail = node;
      return;
    }

    // nth node
    L->head->prev = node;
    node->next = L->head;
    L->head = node;
}
void append(List L, int data){
  Node node = newNode(&data);

   // First node
  if (L->head == NULL) {
    L->head = node;
    L->tail = node;
    return;
  }

  // nth node
  node->prev = L->tail;
  L->tail->next = node;
  L->tail = node;
}
void insertBefore(List L, int data){
    if (length(L) <= 0) {
      fprintf(stderr, "List.c: insertBefore() called on an empty list\n");
      return;
    }
    if (index(L) < 0) {
      fprintf(stderr, "List.c: insertBefore() invalid index\n");
      return;
    }

    // Equivalent to prepending
    if (L->cursor == L->head) {
      prepend(L, data);
      return;
    }

    // prepare node
    Node node = newNode(&data);
    node->prev = L->cursor->prev;
    node->next = L->cursor;

    // Insert at cur
    L->cursor->prev->next = node;
    L->cursor->prev = node;
}
void insertAfter(List L, int data){
    if (length(L) <= 0) {
      fprintf(stderr, "List.c: insertAfter() called on an empty list\n");
      return;
    }
    if (index(L) < 0) {
      fprintf(stderr, "List.c: insertAfter() invalid index\n");
      return;
    }

      // Equivalent to appending
    if (L->cursor == L->tail) {
      append(L, data);
      return;
    }

    // Prepare node
    Node node = newNode(&data);
    node->prev = L->cursor;
    node->next = L->cursor->next;

    // Insert node
    L->cursor->next = node;
    L->cursor->next->prev = node;
}
void deleteFront(List L){
    if (length(L) <= 0) {
      fprintf(stderr, "List.c: deleteFront() called on an empty list\n");
      return;
    }

    removeNode(L, L->head);
}
void deleteBack(List L){
    if (length(L) <= 0) {
      fprintf(stderr, "List.c: deleteBack() called on an empty list\n");
      return;
    }

    removeNode(L, L->tail);
}
void delete(List L){
    if (length(L) <= 0) {
      fprintf(stderr, "List.c: delete() called on an empty list\n");
      return;
    }
    if (index(L) < 0) {
      fprintf(stderr, "List.c: delete() invalid index\n");
      return;
    }

    removeNode(L, L->cursor);
}
// Custom node remover
void removeNode(List L, Node node) {
      // Node n is cursor so set cur to (-1)
    if (L->cursor == node)
      freeNode(L->cursor);
    // buffer


    // Only one node in the list
    if (length(L) == 1) {
      freeNode(L->head);
      freeNode(L->tail);
      return;
    }

    // Remove head
    if (node == L->head) {
      freeNode(L->head->next->prev);
      L->head = L->head->next;
      return;
    }

    // Remove tail
    if (node == L->tail) {
      freeNode(L->tail->prev->next);
      L->tail = L->tail->prev;
      return;
    }

    // Remove body
    Node cur = L->head;
    while (cur->next != NULL) {
      if (cur == node) {
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        return;
      }
      cur = cur->next;
    }
}

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L){
    Node cur = L->head;
    while (cur != NULL) {
      fprintf(out, "%d ", *(cur->item) );
      cur = cur->next;
    }

}
List copyList(List L){
    List copy = newList();
    Node cur = L->head;

    while (cur != NULL) {
      append(copy, *(cur->item));
      cur = cur->next;
    }

    return copy;
}