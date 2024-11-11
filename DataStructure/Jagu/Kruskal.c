#include <stdio.h>
#include <stdlib.h>

#define True 1;
#define False 0;
#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];

typedef struct Edge {
	int start, end, weight;
}Edge;

typedef struct GraphType {
	int n;
	int nvertex;
	Edge edges[2 * MAX_VERTICES];
}GraphType;

void set_init(int n) {
	for (int i = 0; i < n; i++) parent[i] = -1;
}

int set_find(int curr) {
	if (parent[curr] == -1) return curr;
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}

void set_union(int a, int b) {
	int root1 = set_find(a);
	int root2 = set_find(b);
	if (root1 != root2) parent[root1] = root2;
}

void graph_init(GraphType* g) {
	g->n = g->nvertex = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = 0;
	}
}

void insert_edge(GraphType* g, int start, int end, int w) {
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}

int compare(const void* a, const void* b) { 
	Edge* x = (Edge*)a;
	Edge* y = (Edge*)b;
	return (x->weight - y->weight);
}

void kruskal(GraphType* g) {
	int edge_accepted = 0;
	int uset, vset = 0;
	Edge e;

	set_init(g->nvertex);
	qsort(g->edges, g->n, sizeof(Edge), compare);

	printf("크루스칼 최소 신장 트리 알고리즘 \n");
	int i = 0;
	while (edge_accepted < (g->nvertex - 1)) {
		e = g->edges[i];
		uset = set_find(e.start);
		vset = set_find(e.end);
		if (uset != vset) {
			printf("간선 (%d,%d) %d 선택\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);
		}
		i++;
	}
}

int main() {
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	g->nvertex = 7;
	insert_edge(g, 0, 1, 29);
	insert_edge(g, 1, 2, 16);
	insert_edge(g, 2, 3, 12);
	insert_edge(g, 3, 4, 22);
	insert_edge(g, 4, 5, 27);
	insert_edge(g, 5, 6, 10);
	insert_edge(g, 6, 7, 15);
	insert_edge(g, 7, 8, 18);
	insert_edge(g, 8, 9, 25);

	kruskal(g);
	free(g);
	return 0;
}