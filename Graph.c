/***
 * Tanvi Herwadkar
 * therwadk
 * 2023 Fall CSE101 PA2
 * Graoh.c
 * Implements Graph ADT
***/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "List.h"

enum colors{white, gray, black};

typedef struct GraphObj {
	List *adjList;
	int order;	//vertices
	int size;	//edges
	
	int *distances;	//distance of path
	int *colors;	//visited array, while BFS
	int *parents;	//previous node, while BFS
	int source;	//starting node
}GraphObj;

Graph newGraph(int n) {
	Graph G;
	G = malloc(sizeof(GraphObj));
	G->adjList = calloc((n+1), sizeof(List));
	for (int i = 1; i <= n; i++) {
		G->adjList[i] = newList();
	}
	G->order = n;
	G->size = 0;
	G->distances = calloc((n+1), sizeof(int));
	for (int i = 1; i < n+1; i++) {
		G->distances[i] = INF;
	}
	G->colors = calloc((n+1), sizeof(int));
	for (int i = 1; i < n+1; i++) {
		G->colors[i] = white;
	}
	G->parents = calloc((n+1), sizeof(int));
	for (int i = 1; i < n+1; i++) {
                G->parents[i] = NIL;
        }
	G->source = NIL;
	return (G);
}

void freeGraph(Graph *pG) {
	if (pG!=NULL && *pG!=NULL) {
		for (int i = 0; i < ((*pG)->order) + 1; i++) {
			freeList(&((*pG)->adjList[i]));
		}
		free((*pG)->adjList);
		free((*pG)->distances);
		free((*pG)->colors);
		free((*pG)->parents);
		free(*pG);
		*pG = NULL;
	}
}

int getOrder(Graph G) {
	if (G == NULL) {
		fprintf(stderr, "Graph Error: calling getOrder() on a NULL Graph ref\n");
		exit(1);
	}
	return G->order;
}

int getSize(Graph G) {
        if (G == NULL) {
                fprintf(stderr, "Graph Error: calling getSize() on a NULL Graph ref\n");
		exit(1);
        }
        return G->size;
}

int getSource(Graph G) {
        if (G == NULL) {
                fprintf(stderr, "Graph Error: calling getSource() on a NULL Graph ref\n");
                exit(1);
        }
	return G->source;
}

int getParent(Graph G, int u) {	
        if (G == NULL) {
                fprintf(stderr, "Graph Error: calling getParent() on a NULL Graph ref\n");
                exit(1);
        }
	if ( 1 > u || u > getOrder(G)) {
                fprintf(stderr, "Graph Error: calling getParent() on an invalid vertex\n");
                exit(1);
        }
	if (G->parents[u] == 0) {
		fprintf(stderr, "Graph Error: calling getParent() on a vertex without a parent\n");
		exit(1);
	}
	return G->parents[u];
}

void getPath (List L, Graph G, int u) {
	if (L == NULL) {
		fprintf(stderr, "Graph Error: NULL List ref passed into getPath()");
		exit(1);
	}
	if (G == NULL) {
		fprintf(stderr, "Graph Error: calling getPath() on a NULL Graph ref");
		exit(1);
	}
	if ( 1 > u || u > getOrder(G)) {
                fprintf(stderr, "Graph Error: calling getPath() on an invalid vertex\n");
                exit(1);
        }
	if (getSource(G) == 0) {
		fprintf(stderr, "Graph Error: calling getPath() before BFS has run");
		exit(1);
	}
	int s = getSource(G);
	if (s == u) {
		append(L, s);
	}
	else if (G->parents[u] == NIL) {
		append(L, NIL);
		return;
	}
	else {
		getPath(L, G, G->parents[u]);
		append(L, u);
	}
}

int getDist(Graph G, int u) {
	if (G == NULL) {
		fprintf(stderr, "Graph Error: calling getDist() on a NULL Graph ref\n");
		exit(1);
	}
	if ( 1 > u || u > getOrder(G)) {
		fprintf(stderr, "Graph Error: calling getDist() on an invalid vertex\n");
                exit(1);
	}
	return G->distances[u];
}

// Manipulator functions --------------------------------------------------------------------------------------

void makeNull(Graph G) {
	if (G == NULL) {
		fprintf(stderr, "Graph Error: calling makeNull() on a NULL Graph ref\n");
		exit(1);
	}	
	int n = getOrder(G);
	for (int i = 1; i <= n; i++) {
		freeList(&(G->adjList[i]));
		G->adjList[i] = newList();
	}
	G->size = 0;
	for (int i = 1; i < n+1; i++) {
		G->distances[i] = INF;
	}
	for (int i = 1; i < n+1; i++) {
		G->colors[i] = white;
	}	
	for (int i = 1; i < n+1; i++) {
		G->parents[i] = NIL;
	}
	G->source = NIL;
}

void addEdge(Graph G, int u, int v) {
	addArc(G, u, v);
	addArc(G, v, u);
	G->size -= 1;	
}

void addArc(Graph G, int u, int v) {
	if (u > getOrder(G) || u <= 0) {
		fprintf(stderr, "Graph Error: calling addArc() on a vertex that doesn't exist\n");
		exit(1);
	}
	if (v > getOrder(G) || v <= 0) {
		fprintf(stderr, "Graph Error: calling addArc() to add a vertex %d that doesn't exist\n", v);
		exit(1);
	}
	bool doub = false;
	if (length(G->adjList[u]) == 0) {
		append(G->adjList[u], v);
	}
	else {	
		for(moveFront(G->adjList[u]); index(G->adjList[u])>=0; moveNext(G->adjList[u])) {
			if (v == get(G->adjList[u])){
				doub = true;
				break;
			}	
			if (v < get(G->adjList[u])) {
				insertBefore(G->adjList[u], v);
				break;
			}
		}
		if (index(G->adjList[u]) < 0 && !doub) {
			append(G->adjList[u], v);
		}
	}
	G->size += 1;
}

void BFS(Graph G, int s) {
	if (G == NULL) {
		fprintf(stderr, "Graph Error: calling BFS() on a NULL Graph ref\n");
		exit(1);
	}
	G->source = s;
	for (int x = 1; x <= getOrder(G); x++) {
		if (x == s) {
			continue;
		}
		G->colors[x] = white;
		G->distances[x] = INF;
		G->parents[x] = NIL;
	}
	G->colors[s] = gray;
	G->distances[s] = 0;
	G->parents[s] = NIL;
	List Q = newList();
	append(Q, s);
	while (length(Q) != 0) {
		int x = front(Q);
		moveFront(Q);
		delete(Q);
		for (moveFront(G->adjList[x]); index(G->adjList[x])>=0; moveNext(G->adjList[x])){
			int y = get(G->adjList[x]);
			if (G->colors[y] == white) {
				G->colors[y] = gray;
				G->distances[y] = G->distances[x] + 1;
				G->parents[y] = x;
				append(Q, y);
			}
		} 
		G->colors[x] = black;
	}
	freeList(&Q);
}


void printGraph(FILE* out, Graph G) {
	if (G == NULL) {
		fprintf(stderr, "Graph Error: calling printGraph() on a NULL Graph ref\n");
		exit(1);
	}
	if (out == NULL) {
		fprintf(stderr, "Graph Error: calling printGraph() on a NULL FILE ref\n");
		exit(1);
	}
	for (int i = 1; i <= G->order; i++) {
		fprintf(out, "%d: ", i);
		if (G->adjList[i] != NULL) {
			printList(out, G->adjList[i]);	
		}
		if (i != G->order) {
			fprintf(out, "\n");
		}
	}	
}
