#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* array;
    int count; // Èü ¾ÈÀÇ Ç×¸ñ °³¼ö
    int capacity; // ÈüÀÇ ¿ë·®
    int heap_type; //ÈüÀÇ Á¾·ù
} Heap;

Heap* CreateHeap(int capacity, int heap_type) {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    if (h == NULL) {
        printf("Memory Error");
        return;
    }
    h->heap_type = heap_type; //heap type ÀÌ 0 = max  1 = min
    h->count = 0;
    h->capacity = capacity;
    h->array = (int*)malloc(sizeof(int) * h->capacity);
    if (h->array == NULL) {
        printf("Memory Error");
        return;
    }
    return h;
}

int Parent(Heap* h, int i) {
    if (i <= 0 || i >= h->count)
        return -1;
    return (i - 1) / 2;
}

int LeftChild(Heap* h, int i) {
    int left = 2 * i + 1;
    if (left >= h->count)
        return -1;
    return left;
}

int RightChild(Heap* h, int i) {
    int right = 2 * i + 2;
    if (right >= h->count)
        return -1;
    return right;
}

void PercolateDown(Heap* h, int i) {
    int l, r, max, temp;
    l = LeftChild(h, i);
    r = RightChild(h, i);
    if (l != -1 && h->array[l] > h->array[i]) max = l;
    else max = i;
    if (r != -1 && h->array[r] > h->array[max]) max = r;
    if (max != i) {
        temp = h->array[i];
        h->array[i] = h->array[max];
        h->array[max] = temp;
        PercolateDown(h, max);
    }
}

void PercolateUp(Heap* h, int i) {
    int temp;
    int parent = Parent(h, i);

    while (i > 0 && h->array[parent] < h->array[i]) {
        temp = h->array[i];
        h->array[i] = h->array[parent];
        h->array[parent] = temp;
        i = parent;
        parent = Parent(h, i);
    }
}

void Insert_Max_Heap(Heap* h, int data) {
    if (h->count == h->capacity) {
        printf("Heap is full\n");
        return;
    }
    h->count++;
    int i = h->count - 1;
    h->array[i] = data;

    PercolateUp(h, i);
}

int Delete_Max_Heap(Heap* h) {
    int data;
    if (h->count == 0) return-1;
    data = h->array[0];
    h->array[0] = h->array[h->count - 1];
    h->count--;
    PercolateDown(h, 0);
    return data;
}