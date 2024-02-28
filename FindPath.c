/***
 * Tanvi Herwadkar
 * therwadk
 * 2023 Fall CSE101 PA2
 * FindPath.c 
 * Main client for Graph ADT + BFS
***/ 

#include<stdio.h>
#include <assert.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

int main (int argc, char *argv[]) {
	FILE *in, *out;
	char line[4];
	(void) line;

	//check for 2 arguments
	if (argc != 3) {
		fprintf(stderr,"Usage: %s <input file> <output file>\n", argv[0]);
                exit(1);	
	}

	in = fopen(argv[1], "r");
        if (in == NULL) {
                fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
                exit(1);
        }

	out = fopen(argv[2], "w");
        if (out == NULL) {
                fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
                exit(1);
        }
	
	int num_nodes;
	fscanf(in, "%d", &num_nodes);
	
	Graph G = newGraph(num_nodes);
	
	int from; int to;
	while (fscanf(in, "%d %d", &from, &to) != EOF) {
		if (from == 0 && to == 0) {
			break;
		}
		assert(from != 0 && to != 0);
		addEdge(G, from, to);	
	}
	
	printGraph(out, G);

	while (fscanf(in, "%d %d", &from, &to) != EOF) {
		if (from == 0 && to == 0) {
			break;
		}
		fprintf(out, "\n\n");
		assert(from != 0 && to != 0);
		BFS(G, from);
		int dist = getDist(G, to);
		if (dist == -1) {
			fprintf(out, "The distance from %d to %d is infinity\nNo %d-%d path exists", from, to, from, to);	
			continue;
		}
		fprintf(out, "The distance from %d to %d is %d\n", from, to, dist);
		fprintf(out, "A shortest %d-%d path is: ", from, to);
		List L = newList();
		getPath(L, G, to);
		printList(out, L);
	}
	
	fprintf(out, "\n");

	freeGraph(&G);

	fclose(in);
	fclose(out);
	
	return 0;
}
