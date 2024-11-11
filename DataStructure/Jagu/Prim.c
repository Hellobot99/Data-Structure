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

int selceted[MAX_VERTICES];
int distance[MAX_VERTICES];

int get_min_vertex(int n) {
	int v, i;
	for (i = 0; i < n; i++) {
		if (!selceted[i]) {
			v = i;
			break;
		}
	}
	for (i = 0; i < n; i++) {
		if (!selceted[i] && (distance[i] < distance[v])) v = i;
	}
	return v;
}

void prim(GraphType* g, int s) {
	int i, u, v;
	for (u = 0; u < g->n; u++) {
		distance[u] = INF;
	}
	distance[s] = 0;
	for (i - 0; i < g->n; i++) {
		u = get_min_vertex(g->n);
		selceted[u] = True;
		if (distance[u] == INF)return;
		printf("정점 %d 추가\n", u);
		for (v = 0; v < g->n; v++) {
			if (g->weight[u][v] != INF)
				if (!selceted[v] && g->weight[u][v] < distance[v])
					distance[v] = g->weight[u][v];
		}

	}
}

