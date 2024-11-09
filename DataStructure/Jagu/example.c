#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(x,y) x>y?x:y

typedef struct Heap {
	int *arr;
	int count;
	int capacity;
	int heap_type;
}Heap;

Heap* CreateHeap(int capacity, int heap_type) {
	Heap* h = (Heap*)malloc(sizeof(Heap));
	h->arr = (int*)malloc(sizeof(int) * capacity);
	h->count = 0;
	h->heap_type = heap_type;
}

int Parent(Heap* h, int i) {
	return (i - 1) / 2;
}

int LeftChild(Heap* h, int i) {
	return i * 2;
}

int RightChild(Heap* h, int i) {
	return i * 2 + 1;
}

void PercolateUp(Heap* h, int i) {
	int temp;
	int parent = Parent(h, i);
	if (h->arr[parent] < h->arr[i] && i > 0) {
		temp = h->arr[parent];
		h->arr[parent] = h->arr[i];
		h->arr[i] = temp;

		PercolateUp(h, parent);
	}
}

void PercolateDown(Heap* h, int i) {
	int temp,m=i;
	int lc = LeftChild(h, i);
	int rc = RightChild(h, i);
	
	if (lc < h->capacity && h->arr[lc] > h->arr[m]) m = lc;
	if (rc < h->capacity && h->arr[rc] > h->arr[m]) m = rc;
	
	if (h->arr[m] > h->arr[i]) {
		temp = h->arr[m];
		h->arr[m] = h->arr[i];
		h->arr[i] = temp;

		PercolateDown(h, m);
	}
}

void insert(Heap* h, int data) {
	if (h == NULL) h = CreateHeap(20, 1);
	h->arr[h->count++] = data;
	PercolateUp(h, h->count-1);
}

int delete(Heap* h) {
	if (h == NULL) return;
	int result = h->arr[0];
	h->arr[0] = h->arr[--(h->count)];
	PercolateDown(h, 0);
	return result;
}

int main() {
	

	return 0;
}