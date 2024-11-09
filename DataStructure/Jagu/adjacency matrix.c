#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50
#define MAX_QUEUE_SIZE 10
typedef int element;

typedef struct GraphType {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

typedef struct QueueType {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void queue_init(QueueType* q) {
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

int is_full(QueueType* q) {
	return((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item) {
	if (is_full(q)) return;
	q->rear = q->rear + 1 % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

element dequeue(QueueType* q) {
	if (is_empty(q))return;
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

void bfs_mat(GraphType* g,int v) {
	int w;
	QueueType q;
	queue_init(&q);
	visited[v] = 1;
	printf("%d 방문 -> ", v);
	enqueue(&q, v);
	while (!is_empty(&q)) {
		v = dequeue(&q);
		for (w = 0; w < g->n; w++) {
			if (g->adj_mat[v][w] && !visited[w]) {
				visited[w] = 1;
				printf("%d 방문 -> ", w);
				enqueue(&q, w);
			}
		}
	}
}

void init_adj(GraphType* g);
void insert_vertex_adj(GraphType* g, int v);
void insert_edge_adj(GraphType* g, int start, int end);
void print_adj_mat(GraphType* g);
void dfs_mat(GraphType* g, int v);


int main() {

	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	for (int i = 0; i < 4; i++) {
		insert_vertex(g, i);
	}
	insert_edge_adj(g, 0, 1);
	insert_edge_adj(g, 0, 2);
	insert_edge_adj(g, 0, 3);
	insert_edge_adj(g, 1, 2);
	insert_edge_adj(g, 2, 3);
	print_adj_mat(g);

	free(g);

	return 0;
}

void init_adj(GraphType* g) {
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++) g->adj_mat[r][c] = 0;
}

void insert_vertex_adj(GraphType* g, int v) {
	if (((g->n) + 1) > MAX_VERTICES) {
		return 0; //할당 실패
	}
	g->n++;
}

void insert_edge_adj(GraphType* g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		return 0;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

void print_adj_mat(GraphType* g) {
	for (int i = 0; i < g->n; i++) {
		for (int j = 0; j < g->n; j++) {
			printf("%2d ", g->adj_mat[i][j]);
		}
		printf("\n");
	}
}

int visited[MAX_VERTICES];
void dfs_mat(GraphType* g, int v) {
	int w;
	visited[v] = 1;
	printf("정점 %d -> ", v);
	for (w = 0; w < g->n; w++) {
		if (g->adj_mat[v][w] && !visited[w]) dfs_mat(g, w);
	}
}