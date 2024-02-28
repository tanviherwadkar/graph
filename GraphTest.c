/***
 * Tanvi Herwadkar
 * therwadk
 * 2023 Fall CSE101 PA2
 * GraohTest.c
 * Test client for Graph ADT
***/ 

#include <stdio.h>
#include "Graph.h"
#include <stdlib.h>
#include <stdbool.h>
/* UD Graph
int main (int argc, char *argv[]) {
	Graph G = newGraph(6);
	addEdge(G, 1, 2);
	addEdge(G, 1, 3);	
	addEdge(G, 2, 4);
	addEdge(G, 2, 5);
	addEdge(G, 2, 6);
	addEdge(G, 3, 4);
	addEdge(G, 4, 5);
	//addEdge(G, 5, 6);
	addEdge(G, 6, 5);
	BFS(G, 3);
	printGraph(stdout, G);
	printf("\n");
	printf("Path : ");
	List L = newList();
	getPath(L, G, 6);
	printList(stdout, L);
	printf("\n");
	freeList(&L);
	freeGraph(&G);
	return 0;
} */

int main (int argc, char *argv[]) {
	Graph G= newGraph(4);
	addArc(G, 1, 2);
	addArc(G, 1, 3);
	addArc(G, 3, 2);
	addArc(G, 2, 4);
	addArc(G, 4, 3);
	BFS(G, 3);
	makeNull(G);
	printGraph(stdout, G);
	List L = newList();
	getPath(L, G, 4);
	printf("\n");
	printf("Path : ");
	printList(stdout, L);
	printf("\n");
	printf("distance = %d\n", getDist(G, 4));
	printf("source   = %d\n", getSource(G));
	printf("\n\n\n");

	List old = newList();
	append(old, 1);
	append(old, 2);
	append(old, 3);
	clear(old);
	printf("Path old : ");
	printList(stdout, old);
	printf("\n");
	List new = copyList(old);
	printf("Path new : ");
	printList(stdout, new);
	printf("\n");
	freeList(&old);
	freeList(&new);

	freeList(&L);
	freeGraph(&G);
	return 0;
} 

/* List ADT
int main (int argc, char *argv[]) {
	List L = newList();
	append(L, 1);
	append(L, 2);
	append(L, 3);
	moveFront(L);
	moveNext(L);

	printf("index %d\ncursor %d\n", index(L), get(L));	
	List Lcpy = copyList(L);
	
	printf("index %d\ncursor %d\n", index(L), get(L));	

	freeList(&Lcpy);
	freeList(&L);
} */
