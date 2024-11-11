#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#define MAX_STACK_SIZE 100
typedef int element;

typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct GraphType {
	int n;
	GraphNode* adj_list[MAX_VERTICES];
}GraphType;

GraphType* create_graph() {
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	return g;
}

void init(GraphType* g) {
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++) {
		g->adj_list[v] = NULL;
	}
}

void insert_vertex(GraphType* g, int v) {
	if (((g->n) + 1) > MAX_VERTICES) {
		return;
	}
	g->n++;
}

void insert_edge(GraphType* g, int u, int v) {
	GraphNode* node;
	if (u >= g->n || v >= g->n) return;
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}


typedef struct StackType {
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s) {
	return (s->top == -1);
}

int is_full(StackType* s) {
	return (s->top == MAX_STACK_SIZE-1);
}

void push(StackType* s, element item) {
	if (is_full(s)) {
		return;
	}
	else s->stack[++(s->top)] = item;
}

element pop(StackType* s) {
	if (is_empty(s)) {
		return;
	}
	else return s->stack[(s->top)--];
}

int topo_sort(GraphType* g) {
	int i;
	StackType s;
	GraphNode* node;

	int* in_degree = (int*)malloc(sizeof(int)*g->n);
	for (i = 0; i < g->n; i++) {
		in_degree[i] = 0;
	}
	for (i = 0; i < g->n; i++) {
		GraphNode* node = g->adj_list[i];
		while (node) {
			in_degree[node->vertex]++;
			node = node->link;
		}
	}
	init_stack(&s);
	for (i = 0; i < g->n; i++) {
		if (!in_degree[i]) push(&s, i);
	}
	while (!is_empty(&s)) {
		int w;
		w = pop(&s);
		printf("Á¤Á¡ %d ->", w);
		node = g->adj_list[w];
		while (node) {
			int u = node->vertex;
			in_degree[u]--;
			if (in_degree == 0) push(&s, u);
			node = node->link;
		}
	}
}




