#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
typedef struct {
	int key;
}element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

HeapType* create_heap();
void init_heap(HeapType* heap);
void insert_max_heap(HeapType* h, element item);
element delete_max_heap(HeapType* h);
void insert_min_heap(HeapType* h, element item);
element delete_min_heap(HeapType* h);
void heap_sort(element arr[], int n);

int main() {
	element arr[5] = { 1,15,82,25,34 };
	printf("%d %d %d %d %d\n", arr[0].key, arr[1].key, arr[2].key, arr[3].key, arr[4].key);
	heap_sort(arr, 5);
	printf("%d %d %d %d %d", arr[0].key, arr[1].key, arr[2].key, arr[3].key, arr[4].key);

	return 0;
}

HeapType* create_heap() {
	HeapType* heap = (HeapType*)malloc(sizeof(HeapType));
	if (heap == NULL) {
		printf("메모리 할당 실패\n");
		return NULL;
	}
	heap->heap_size = 0;
	return heap;
}
void init_heap(HeapType* heap) {
	heap->heap_size = 0;
}

void insert_max_heap(HeapType* h, element item) {
	int a;
	a = ++(h->heap_size);

	while (a != 1 && h->heap[a / 2].key < item.key) {
		h->heap[a] = h->heap[a / 2];
		a /= 2;
	}
	h->heap[a] = item;
}
element delete_max_heap(HeapType* h) {
	int parent = 1, child = 2;
	element item = h->heap[1];
	element temp = h->heap[(h->heap_size)--];
	while (child <= h->heap_size) {
		if (child < h->heap_size && h->heap[child].key < h->heap[child + 1].key) child++;
		if (temp.key >= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void insert_min_heap(HeapType* h, element item) {
	int a;
	a = ++(h->heap_size);

	while (a != 1 && h->heap[a / 2].key > item.key) {
		h->heap[a] = h->heap[a / 2];
		a /= 2;
	}
	h->heap[a] = item;
}
element delete_min_heap(HeapType* h) {
	int parent = 1, child = 2;
	element item = h->heap[1];
	element temp = h->heap[(h->heap_size)--];
	while (child <= h->heap_size) {
		if (child < h->heap_size && h->heap[child].key > h->heap[child + 1].key) child++;
		if (temp.key <= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void heap_sort(element arr[], int n) {
	HeapType* heap = create_heap();
	init_heap(heap);
	for (int i = 0; i < n; i++) {
		insert_max_heap(heap, arr[i]);
	}

	for (int i = n - 1; i >= 0; i--) {
		arr[i] = delete_max_heap(heap);
	}

	free(heap);
}
