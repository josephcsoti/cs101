/*------------------------------------------------
File Name: Graph.c
Desc: Graph ADT using our List ADT

Name:  Joseph Csoti
CruzID: 1617438 // jcsoti
Class:  CMPS 101
Date:  12/05/18
------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "Graph.h"

#define WHITE 0
#define BLACK 1
#define GRAY  2

// Structs ------------

// private GraphObj type
typedef struct GraphObj{
  List *adj;
  int *color;
  int *parent;
  int *dist;
  int *discover;
  int *finish;
  int order;
  int size;
} GraphObj;

// Constructors-Destructors --------------------------

// Returns a new Graph OBJ
Graph newGraph(int n){

  // Allocate memory
  Graph G = malloc(sizeof(struct GraphObj));
  G->adj = calloc(n + 1, sizeof(List));
  G->color = calloc(n + 1, sizeof(int));
  G->parent = calloc(n + 1, sizeof(int));
  G->dist = calloc(n + 1, sizeof(int));
  G->discover = calloc(n + 1, sizeof(int));
  G->finish = calloc(n + 1, sizeof(int));

  // Init each vertex to starting state
  for (int i = 1; i <= n; i++){
    G->adj[i] = newList();
    G->color[i] = WHITE;
    G->parent[i] = NIL;
    G->dist[i] = INF;
    G->discover[i] = UNDEF;
    G->finish[i] = UNDEF;
  }

  // set info
  G->order = n;
  G->size = 0;
  return G;
}

// Frees Graph from memory
void freeGraph(Graph* pG){
  Graph g = *pG;
  for (int i = 1; i <= getOrder(g); i++){
    freeList(&(g->adj[i]));
  }

  free(g->color);
  free(g->parent);
  free(g->dist);
  free(g->adj);
  free(g->discover);
  free(g->finish);

  free(*pG);
  *pG = NULL;
}

// Define Private Helpers --------------------------------------------
int pop(List S);
void push(List S, int x);
void visit(Graph G, List S, int u, int *time);

// Access functions ------------------------------------------------

// Returns the order of G
int getOrder(Graph G){
  return G->order;
}

// Returns the size of G
int getSize(Graph G){
  return G->size;
}

// Returns the parent
// Pre: 1 <= u <= order
int getParent(Graph G, int u){
  if (u < 1 && u > getOrder(G)){
    printf("Error: Graph.c - getParent() called on an invalid vertex\n");
    exit(1);
  }
  return G->parent[u];
}

int getDiscover(Graph G, int u){
  if (u < 1 && u > getOrder(G)){
    printf("Error: Graph.c - getDiscover() called on an invalid vertex\n");
    exit(1);
  }
  return G->discover[u];
}

int getFinish(Graph G, int u){
    if (u < 1 && u > getOrder(G)){
    printf("Error: Graph.c - getFinish() called on an invalid vertex\n");
    exit(1);
  }
  return G->finish[u];
}


// Manipulation procedures ---------------------------------

// Clear graph to init state
void makeNull(Graph G){
  for (int i = 1; i <= getOrder(G); i++)
    clear(G->adj[i]);
  G->size = 0;
}

// Inserts vertex x into the list using the List ADT properties
void insertIntoList(List list, int x){
  // List is empty
  if (length(list) == 0){
    append(list, x);
    return;
  }
  // In body
  for (moveFront(list); index(list) != -1; moveNext(list)){
    // Found node
    if(x < get(list)){
      insertBefore(list, x); // Insert before
      break;
    }
  }
  // Reached end of the list
  if(index(list) == -1)
    append(list, x);
}

// Adds edge to Graph (connects u/v)
// Pre: 1 <= u and v <= order
void addEdge(Graph G, int u, int v){
  if ( (u < 1 && u > getOrder(G)) || (v < 1 && v > getOrder(G)) ){
    printf("Error: Graph.c - addEdge() called on an invalid vertex, %d\n", u);
    exit(1);
  }

  //Get ADJ lists
  List A = G->adj[u];
  List B = G->adj[v];

  // Insert edge to each vertex ADJ list
  insertIntoList(A, v);
  insertIntoList(B, u);

  G->size++;
}

// Adds DIRECTED edge to Graph (connects ONLY u TO v)
// Pre: 1 <= u and v <= order
void addArc(Graph G, int u, int v){
  if ( (u < 1 && u > getOrder(G)) || (v < 1 && v > getOrder(G)) ){
    printf("Error: Graph.c - addArc() called on an invalid vertex, %d\n", u);
    exit(1);
  }

  //Get ADJ list
  List A = G->adj[u];

  // Insert edge to vertex ADJ list
  insertIntoList(A, v);

  G->size++;
}

// Run DFS
/* Pre: length(S)==getOrder(G) */
void DFS(Graph G, List S){
  if (G == NULL) {
    printf("Error: Graph.c - DFS() called on a NULL graph");
    exit(1);
  }
  if (S == NULL) {
    printf("Error: Graph.c - DFS() called on a NULL list");
    exit(1);
  }
  if (length(S) != getOrder(G)) {
    printf("Error: Graph.c - DFS() called on a bad list");
    exit(1);
  }
  // Init stage
  for (int i = 1; i <= getOrder(G); i++) {
    G->color[i] = WHITE;
    G->parent[i] = NIL;
    G->discover[i] = UNDEF;
    G->finish[i] = UNDEF;
  }
  int time = 0;
  // Visit each vertex in G
  List T = copyList(S);
  clear(S);
  // Visit each node in ADJ Cycle through the adjacency listList
  for (moveFront(T); index(T) != -1; moveNext(T)) {
    int u = get(T);
    if (G->color[u] == WHITE) {
      visit(G, S, u, &time);
    }
  }
  freeList(&T);
}

void visit(Graph G, List S, int u, int *time) {
  if (S == NULL || time == NULL) {
    printf("Error: Graph.c - visit() called on an null list, %d\n", u);
    exit (1);
  }
  G->color[u] = GRAY;
  G->discover[u] = ++(*time);
  List adj = G->adj[u];

  // Visit each node recurisvely in the ADJ list
  for (moveTo(adj, 0); index(adj) != -1; moveNext(adj)) {
    int y = get(adj);
    if (G->color[y] == WHITE) {
      G->parent[y] = u;
      visit(G, S, y, time);
    }
  }
  // Finished and push it onto the stack
  G->color[u] = BLACK;
  G->finish[u] = ++(*time);
  push(S, u);
}
// pop
int pop(List S) {
  if (S == NULL) {
    printf("Error: Graph.c - pop() called on an null list");
    exit(1);
  }
  if (length(S) == 0) {
    printf("Error: Graph.c - visit() called on an empty list");
    exit(1);
  }
  int x = front(S);
  deleteFront(S);
  return(x);
}
// Push
void push (List S, int x) {
  prepend(S, x);
}

// Other operations --------------------------------

Graph transpose(Graph G){
  if (G == NULL) {
        printf("Error: Graph.c - transpose() called on an null graph");
  }
  Graph T = newGraph(getOrder(G));
  for (int i = 1; i <= getOrder(T); i++) {
    List I = G->adj[i];
    for (moveFront(I); index(I) != -1; moveNext(I)) {
      int x = get(I);
      addArc(T,x,i);
    }
  }
  return (T);
}
Graph copyGraph(Graph G){
  if (G == NULL) {
    printf("Error: Graph.c - copyGraph() called on an null graph");
  }
  Graph T = newGraph(getOrder(G));
  for (int i = 1; i <= getOrder(G); i++) {
    List I = G->adj[i];
    for (moveFront(I); index(I) != -1; moveNext(I)) {
      int x = get(I);
      addArc(T,i,x);
    }
  }
  return (T);
}

// Prints ADJ list of the graph
void printGraph(FILE* out, Graph G){
  for (int i = 1; i <= getOrder(G); i++){
    List list = G->adj[i];
    fprintf(out, "%d:", i);
    for (moveFront(list); index(list) != -1; moveNext(list))
      fprintf(out, " %d", get(list));
    fprintf(out, "\n");
  }
}