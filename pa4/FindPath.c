/*------------------------------------------------
File Name: FindPath.c
Desc: Find the shortest path given a graph

Name:  Joseph Csoti
CruzID: 1617438 // jcsoti
Class:  CMPS 101
Date:  11/25/18
------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"List.h"
#include"Graph.h"

#define MAX_LEN 160

int main(int argc, char* argv[]){
  if( argc != 3 ){
    printf("Usage: FindPath <input> <output >\n");
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
    else addEdge(G, vertex_a, vertex_b);
   }

  // Print graphs current state
  printGraph(out, G);
  fprintf(out, "\n");

  // Do BFS
  while (fgetc(in) != EOF){
    fscanf(in, "%d", &src);
    fscanf(in, "%d", &dest);

    // Trival path
    if (src == 0 && dest == 0)
      break;

    List L = newList();

    BFS(G, src); // Do BFS
    getPath(L, G, dest); // Add paths to list

    int dist = getDist(G, dest); // Get dist

    //No path
    if(dist == INF){
      fprintf(out, "The distance from %d to %d is infinity\n", src, dest);
      fprintf(out, "No %d-%d path exists\n", src, dest);
    }
    else {
      fprintf(out, "The distance from %d to %d is %d\n", src, dest, length(L) - 1);
      fprintf(out, "A shortest %d-%d path is: ", src, dest);
      printList(out, L);
      fprintf(out, "\n");
    }
    // Newline for formating
    fprintf(out, "\n");
    freeList(&L);
  }

  // Clean memory
  freeGraph(&G);
   
  // Close files
  fclose(in);
  fclose(out);
   
  // Properly exit progam
  return(0);
}