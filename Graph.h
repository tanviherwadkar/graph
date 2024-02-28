/***
 * Tanvi Herwadkar
 * therwadk
 * 2023 Fall CSE101 PA2
 * Graoh.h
 * Declares functions for the Graph ADT
***/ 

//******************** Include Statements *****************
#include <stdio.h>
#include "List.h"
#include <stdbool.h>

//******************** Constants **************************
#define INF -1
#define NIL -1

//********************* Exported types *********************
typedef struct GraphObj* Graph;

//********************* Constructor/Destructor *************
//newGraph()
//initializes a new graph with n vertices
Graph newGraph(int n);

//freeGraph()
//frees any memory alloc'd in the graph
void freeGraph(Graph *pG);

//******************** Getter functions ********************
//getOrder()
//returns the number of vertices in the graph
int getOrder(Graph G);

//getSize()
//returns number of edges in the graph
int getSize(Graph G);

//getSource()
//returns source used by most recent bfs call, nil otherwise
int getSource(Graph G);

//getParent
//returns the parent of element in bfs path after most recent bfs call, nil otherwise
//	pre: u (passed in) is a valid vertex
int getParent(Graph G, int u);

//getDist()
//returns the distance from the source to u after bfs is called, inf otherwise
//	pre: u (passed in) is a valid vertex
int getDist(Graph G, int u);

//getPath()
//returns a shortest path from source to u
//	pre: u (passed in) is a valid vertex
void getPath(List L, Graph G, int u);

//******************** Setter Functions ********************
//makeNull()
//resets graph to no-edge (null graph) state
void makeNull(Graph G);

//addEdge()
//adds an edge from u to v and also v to u (undirected graph)
void addEdge(Graph G, int u, int v);

//addArc()
//adds an edge from u to v (directed graph)
void addArc(Graph G, int u, int v);

//BFS()
//performs breadth-first search on the graph
void BFS(Graph G, int s);

//******************** Other Functions **********************
//printGraph()
//prints the adjacency list representation of the graph to passed in file
void printGraph(FILE* out, Graph G);
