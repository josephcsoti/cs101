/*------------------------------------------------
File Name: FindComponents.c
Desc: Find strongly connected components

Name:  Joseph Csoti
CruzID: 1617438 // jcsoti
Class:  CMPS 101
Date:  12/05/18
------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"List.h"
#include"Graph.h"

#define MAX_LEN 160

int main(int argc, char* argv[]){
  // correct args
  if( argc != 3 ){
    printf("Usage: FindComponents <input> <output >\n");
    exit(1);
  }

  // Open file
  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "w");

  // Init vars
  int n = 0;
  int vertex_a = 0;
  int vertex_b = 0;
  int src = 0;
  int dest = 0;

  // Get # of vertices and create graph
  fscanf(in, "%d", &n);
  Graph G = newGraph(n);

  // Get vertices and insert into graph
  while (fgetc(in) != EOF){
    fscanf(in, "%d", &vertex_a); // Get A
    fscanf(in, "%d", &vertex_b); // Get B
    // Skip over 0 verts
    if (vertex_a == 0 && vertex_b == 0) break;
    else addArc(G, vertex_a, vertex_b);
   }

  // Print G current state
  fprintf(out, "Adjacency list representation of G:\n");
  printGraph(out, G);
  fprintf(out, "\n");

  // Create new list w/ vertices of G
  List S = newList();
  for (int i = 1; i <= getOrder(G); i++) {
    append(S, i);
  }
  // Do DFS
  DFS(G, S);
  Graph T = transpose(G);
  DFS(T,S); // run DFS on the newly trnasposed graph

  // Find # of strongly connected componenets
  int count = 0;
  for (moveFront(S); index(S) != -1; moveNext(S)) {
      int x = get(S);

      if (x == -1) continue;

      int p = getParent(T, x);
      if (p == NIL) {
        count++;
        insertBefore(S, -1);
      }
  }

  //printList(out, S);
  int place = length(S) - 1;
  List l = newList();

  fprintf(out, "G contains %d strongly connected components:\n", count);

  // Loop through grapgh
  for (int i = 1; i <= count; i++) {
    fprintf(out, "Component %d: ", i);
    clear(l); // Clear list
    for (moveTo(S, place); index(S) != -1; movePrev(S)) {
      int g = get(S);
      if (g != -1) prepend(l, g); //So we can print int correct, topo order!
      place--;
      if (g == -1) {
      printList(out, l);
      break;
      }
    }
    fprintf(out,"\n");
  }

  // Clear memory
  freeGraph(&G);
   
  // Close files
  fclose(in);
  fclose(out);
   
  // Properly exit progam
  return(0);
}