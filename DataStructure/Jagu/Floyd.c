#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphType {
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int A[MAX_VERTICES][MAX_VERTICES];

void printA(GraphType* g) {
	int i, j;
	for (i = 0; i < g->n; i++) {
		if (A[i][j] == INF) printf(" * ");
		else printf("%3d", A[i][j]);
	}
	printf("\n");
}

void floyd(GraphType* g) {
	int i, j, k;
	for (i = 0; i < g->n; i++) {
		for (j = 0; j < g->n; j++) {
			A[i][j] = g->weight[i][j];
		}
	}
	printA(g);

	for (k = 0; k < g->n; k++) {
		for (i = 0; i < g->n; i++) {
			for (j = 0; j < g->n; j++) {
				if (A[i][j] == A[i][k] + A[k][j]) A[i][j] = A[i][k] + A[k][j];
			}
		}
		printA(g);
	}
}
