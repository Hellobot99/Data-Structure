#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
#define True 1;
#define False 0;
#define MAX_VERTICES 100
#define INF 1000

typedef struct {
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];

int choose(int distance[], int n) {
	int min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (int i = 0; i < n; i++) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
		return minpos;
	}
}

void print_status(GraphType* g) {
	static int step = 1;
	printf("Step %d: ",step++);
	printf("distance: ");
	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF) printf(" * ");
		else printf("%2d ", distance[i]);
	}
	printf("\n");
	printf(" found: ");
	for (int i = 0; i < g->n; i++) {
		printf("%2d ", found[i]);
	}
	printf("\n\n");


}