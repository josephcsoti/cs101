/*------------------------------------------------
File Name: Graph.c
Desc: Graph ADT using our List ADT

Name:  Joseph Csoti
CruzID: 1617438 // jcsoti
Class:  CMPS 101
Date:  11/25/18
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
  int order;
  int size;
  int src;
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

  // Init each vertex to starting state
  for (int i = 1; i <= n; i++){
    G->adj[i] = newList();
    G->color[i] = WHITE;
    G->parent[i] = NIL;
    G->dist[i] = INF;
  }

  // set info
  G->order = n;
  G->size = 0;
  G->src = NIL;
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

  free(*pG);
  *pG = NULL;
}

// Access functions ------------------------------------------------

// Returns the order of G
int getOrder(Graph G){
  return G->order;
}

// Returns the size of G
int getSize(Graph G){
  return G->size;
}

// Returns the source vertex
int getSource(Graph G){
  return G->src;
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

// Returns the dist from BFS source
// Pre: 1 <= u <= order
int getDist(Graph G, int u){
  if (u < 1 && u > getOrder(G)){
    printf("Error: Graph.c - getDist() called on an invalid vertex\n");
    exit(1);
  }

  if (getSource(G) == NIL) return INF;
  else return G->dist[u];
}

// Finds Path in G from given parent
// Pre: 1 <= u <= order
void getPath(List L, Graph G, int u){
  if (u < 1 && u > getOrder(G)){
    printf("Error: Graph.c - getPath() called on an invalid vertex\n");
    exit(1);
  }

  int source = getSource(G);
  int p = G->parent[u];

  if (source == NIL){
    printf("Error: Graph.c - getPath() called on a Graph with an invalid source\n");
    exit(1);
  }

  if (u == source)
    append(L, source); // Apprend source
  else if (p == NIL)
    append(L, NIL); // Parent is nil
  else{
    getPath(L, G, p); // Recurse again
    append(L, u);
  }
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

// Run BFS on a given graph and source
void BFS(Graph G, int s){
  // Init all verticies
  for (int x = 1; x <= getOrder(G); x++){
    G->color[x] = WHITE;
    G->dist[x] = INF;
    G->parent[x] = NIL;
  }

  // Start at the source
  G->src = s;
  G->color[s] = GRAY;
  G->parent[s] = NIL;
  G->dist[s] = 0;

  //Create queue
  List queue = newList();
  append(queue, s);

  while (length(queue) > 0){

    // Get element + "dequeue"
    int x = front(queue);
    deleteFront(queue);
    List adj = G->adj[x];

    // Loop through queue
    for (moveFront(adj); index(adj) != -1; moveNext(adj)){
      int y = get(adj);
      // If vertex is unvisited
      if (G->color[y] == WHITE){
        G->color[y] = GRAY; // "visit" vertex
        G->dist[y] = G->dist[x] + 1; // Add +1 to parent distance
        G->parent[y] = x; // Set parent from where we discovered
        append(queue, y); // Add ADJ list to queue
      }
    }
    G->color[x] = BLACK; // Mark as done
  }
  freeList(&queue);
}

/* Other operations *****************************************************/

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