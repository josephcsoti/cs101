/*------------------------------------------------
File Name: GraphTest.c
Desc: Test file for the graph ADT

Name:  Joseph Csoti
CruzID: 1617438 // jcsoti
Class:  CMPS 101
Date:  11/25/18
------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>

#include"Graph.h"

int main(int argc, char* argv[]) {

  Graph G = newGraph(6);
  addEdge(G, 1, 6);
  addEdge(G, 1, 2);
  addEdge(G, 2, 6);
  addEdge(G, 3, 1);
  addEdge(G, 3, 5);
  addEdge(G, 3, 6);
  addEdge(G, 4, 2);
  addEdge(G, 4, 5);
  addEdge(G, 5, 2);

  printf("G: ");
  printGraph(stdout, G);

  // Try BFS
  BFS(G, 3);

  List paths = newList();
  getPath(paths, G, 1);

  printf("Order: %d\n", getOrder(G));
  printf("Size: %d\n", getSize(G));
  printf("Source: %d\n", getSource(G));
  printf("From 1: Parent=%d, Dist=%d\n", 1, getParent(G, 1), getDist(G, 1));

  // Empty list
  makeNull(G);
  printf("G is now: %s", printGraph(stdout, G));

  // Now testing directed graphs
  G = newGraph(6);
  addArc(G, 1, 4);
  addArc(G, 1, 2);
  addArc(G, 2, 6);
  addArc(G, 2, 1);
  addArc(G, 3, 1);
  addArc(G, 1, 3);
  addArc(G, 3, 4);
  addArc(G, 3, 6);
  addArc(G, 4, 6);
  addArc(G, 4, 2);
  addArc(G, 5, 1);

  printf("G: ");
  printGraph(stdout, G);

  printf("Order: %d\n", getOrder(G));
  printf("Size: %d\n", getSize(G));
  printf("Source: %d\n", getSource(G));

  freeList(&paths)
  freeGraph(&G);
  return (0);
}