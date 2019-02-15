/*------------------------------------------------
File Name: List.c
Desc: Generic List ADT

Name:  Joseph Csoti
CruzID: 1617438 // jcsoti
Class:  CMPS 101
Date:  11/25/18
------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// NodeObj type
typedef struct NodeObj{
  int data;
  struct NodeObj* prev;
  struct NodeObj* next;
} NodeObj;

// ListObj type
typedef struct ListObj{
  Node front;
  Node back;
  Node cursor;
  int length;
  int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// Creates a new node OBJ
Node newNode(int data){
  Node N = malloc(sizeof(NodeObj));
  N->data = data;
  N->prev = NULL;
  N->next = NULL;
  return(N);
}

// Frees node from memory
void freeNode(Node* pN){
  if(pN != NULL && *pN != NULL){
    free(*pN);
    *pN = NULL;
  }
}

// Creates a new List OBJ
List newList(void){
  List L;
  L = malloc(sizeof(ListObj));
  L->front = L->back = L->cursor = NULL;
  L->length = 0;
  L->index = -1;
  return(L);
}

// Frees list from memory
void freeList(List* pL){
  if(pL != NULL && *pL != NULL) { 
    while(length(*pL) != 0) { 
      deleteBack(*pL); 
    }
    free(*pL);
    *pL = NULL;
  }
}

// Access functions -----------------------------------------------------------

// Returns length
int length(List L){
  return L->length;
}

// Returns index of cursor, or -1 if DNE
int index(List L){
  if (L->cursor == NULL){
    L->index = -1;
    return L->index;
  }

  L->index = 0;
  for (Node N = L->front; N != NULL; N = N->next){
    if (N == L->cursor) return L->index;
    L->index++;
  }
  return L->index;
}

// Returns front element in this list
// Pre: length()>0
int front(List L){
  if (length(L) <= 0){
    printf("Error: List.c - front() called on list of length 0\n");
    exit(1);
  }
  return L->front->data;
}

// Returns back element in this List
// Pre: length()>0
int back(List L){
  if (length(L) <= 0){
    printf("Error: List.c - back() called on list of length 0\n");
    exit(1);
  }
  return L->back->data;
}

// Returns cursor element in this list.
// Pre: length()>0, index()>=0
int get(List L){
  if (length(L) <= 0){
    printf ("Error: List.c - get() called on list of length 0\n");
    exit(1);
  }
  if (index(L) < 0){
    printf ("Error: List.c - get() called on undefined cursor\n");
    exit(1);
  }
  return L->cursor->data;
}

// Compare 2 lists
int equals(List A, List B){

  if( A == NULL || B == NULL ){
    printf("Error: List.c - equals()  called on NULL list\n");
    exit(1);
  }

  Node N = A->front;
  Node M = B->front;

  if(length(A) != length(B))
    return 0;

  while(N != NULL){
    if(N->data != M->data)
      return 0;
    N = N->next;
    M = M->next;
  }

  return 1;
}

// Manipulation procedures ----------------------------------------------------

// Empty state
void clear(List L){
  L->front = NULL;
  L->back = NULL;
  L->cursor = NULL;
  L->length = 0;
  L->index = -1;
}

// Move cursor to front
void moveFront(List L){
  L->cursor = L->front;
  L->index = 0;
}

// Move cursor to back
void moveBack(List L){
  L->cursor = L->back;
  L->index = length(L) - 1;
}

// Moves cursor to ith element
void moveTo(List L, int i){
  L->index = 0;
  if (i >= 0 && i <= length(L) - 1){
    for (Node N = L->front; L->index <= i; N = N->next){
      if (L->index == i){
        L->cursor = N;
        break;
      }
      else L->index++;
    }
  }
  else{
    L->cursor = NULL;
    L->index = -1;
  }
}

// Move cursor one node back
void movePrev(List L){
  if (0 < index(L) && index(L) <= length(L) - 1)
    moveTo(L, index(L) - 1);
  else if (index(L) == 0){
    L->index = -1;
    L->cursor = NULL;
  }
}

// Move cursor one node forward
void moveNext(List L){
  if (0 <= index(L) && index(L) < length(L) - 1)
    moveTo(L, index(L) + 1);
  else if (index(L) == length(L) - 1 || L->index == -1){
    L->index = -1;
    L->cursor = NULL;
  }
}

// Prepends a new node to the list
void prepend(List L, int data){

  Node N = newNode(data);
  N->next = L->front;
  N->prev = NULL;

  if (L->front != NULL)
    L->front->prev = N;
  else
    L->back = N;
  
  L->front = N;

  if (L->index != -1)
    L->index++;
  
  L->length++;
}

// Appends a new node to the list
void append(List L, int data){

  Node temp = newNode(data);
  temp->prev = L->back;
  temp->next = NULL;

  if (L->back != NULL)
    L->back->next = temp;
  else
    L->front = temp;

  L->back = temp;
  L->length++;
}

// Inserts new element before cursor element in this List. 
// Pre: length()>0, index()>=0
void insertBefore(List L, int data){
  if (length(L) <= 0){
    printf("Error: List.c - insertBefore() called on list of length 0\n");
    exit(1);
  }
  if (index(L) < 0){
    printf("Error: List.c - insertBefore() called on undefined cursor\n");
    exit(1);
  }

  if (L->cursor == L->front){
    prepend(L, data);
    return;
  }

  Node temp = newNode(data);
  temp->prev = L->cursor->prev;
  temp->next = L->cursor;

  if (L->cursor->prev != NULL)
    L->cursor->prev->next = temp;
  else
    L->front = temp;

  L->cursor->prev = temp;
  L->length++;
}

// Inserts new element after cursor element in this List. 
//Pre: length()>0, index()>=0
void insertAfter(List L, int data){
  if (length(L) <= 0){
    printf("Error: List.c - insertAfter() called on list of length 0\n");
    exit(1);
  }
  if (index(L) < 0){
    printf("Error: List.c - insertAfter() called on undefined cursor\n");
    exit(1);
  }

  if (L->cursor == L->back){
    append(L, data);
    return;
  }

  Node N = newNode(data);
  N->prev = L->cursor;
  N->next = L->cursor->next;

  if (L->cursor->next != NULL)
    L->cursor->next->prev = N;

  L->cursor->next = N;
  L->length++;
}

// Deletes the front element
// Pre: length()>0
void deleteFront(List L){
  if(length(L) <= 0){
    printf("Error: List.c - deleteFront() called on list of length 0\n");
    exit(1);
  }

  Node N = L->front;

  if(N == L->cursor){
   L->cursor = NULL;
   L->index = -1;
  }

  if(length(L) > 1) 
    L->front = L->front->next;
  else {
    L->front = NULL;
    L->back = NULL;
  }

  L->length--;
  freeNode(&N);
}

// Deletes the back element
// Pre: length()>0
void deleteBack(List L){
  if(length(L) <= 0){
    printf("Error: List.c - deleteBack() called on list of length 0\n");
    exit(1);
  }

  Node N = L->back;

  if(N == L->cursor){
   L->cursor = NULL;
   L->index = -1;
  }

  L->back = L->back->prev;
  //L->back->next = NULL;
  L->length--;
  freeNode(&N);
}

// Deletes cursor element in this List. Cursor is undefined after this operation. 
// Pre: length()>0, index()>=0
void delete(List L){
  if (length(L) <= 0){
    printf("Error: List.c - delete() called on list of length 0");
    exit(1);
  }
  if (index(L) < 0){
    printf("Error: List.c - delete() called on undefined cursor");
    exit(1);
  }
  
  if (L->cursor == L->front){
    deleteFront(L);
    return;
  }
  else if (L->cursor == L->back){
    deleteBack(L);
    return;
  }
  L->cursor->prev->next = L->cursor->next;
  L->cursor->next->prev = L->cursor->prev;

  L->index = -1;
  L->cursor = NULL;
  L->length--;
}

// Other operations -----------------------------------------------------------

// Pretty prints list
void printList(FILE* out, List L){
  if(L == NULL){
    printf("Error: List.c - printList() on NULL List\n");
    exit(1);
  }
  for(Node N = L->front; N != NULL; N = N->next){
    fprintf(out, "%d ", N->data);
  }
}

// Copy the list
List copyList(List L){
  List copy = newList();
  for (Node curr = L->front; curr != NULL; curr = curr->next)
    append(copy, curr->data);

  return copy;
}