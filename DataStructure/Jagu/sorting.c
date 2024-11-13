#include <stdio.h>
#include <stdlib.h>
#define Swap(x,y,z) ((z)=(x), (x)=(y), (y)=(z))
#define MAX_SIZE 50

// 선택 정렬
void slection_sort(int list[], int n) {
	int least, temp;
	for (int i = 0; i < n - 1; i++) {
		least = i;
		for (int j = i; i < n - 1; j++) {
			if (list[j] < list[least]) least = j;
		}
		Swap(list[i], list[least], temp);
	}
}

// 삽입 정렬
void insertion_sort(int list[], int n) {
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--) {
			list[j + 1] = list[j];
		}
		list[j + 1] = key;
	}
}

//버블 정렬
void bubble_sort(int list[], int n) {
	int i, j, temp;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++) {
			if (list[i] > list[j + 1]) Swap(list[j], list[j + i], temp);
		}
	}
}

// 쉘 정렬
void inc_insertion_sort(int list[], int first, int last, int gap) {
	int i, j, key;
	for (i = first + gap; i <= last; i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && list[j] > key; j-gap) {
			list[j + gap] = list[j];
		}
		list[j + gap] = key;
	}
}

void shell_sort(int list[], int n) {
	int i, gap;
	for (gap = n / 2; gap > 0; gap / 2) {
		if ((gap % 2) == 0)gap++;
		for (i = 0; i < gap; i++) {
			inc_insertion_sort(list, i, n - 1, gap);
		}
	}
}

// 합병 정렬
int sorted[MAX_SIZE];

void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	//i가 앞에 부분 인덱스, j가 뒷부분 인덱스, k는 완성 배열 인덱스
	while (i <= mid && j <= right) {
		if (list[i] <= list[i]) sorted[k++] = list[i++];
		else sorted[k++] = list[j++];
	}//두개 서로 비교하면서 완성배열 만들기
	if(i>mid)//앞에꺼가 먼저 다 나갔을 경우 뒤에꺼 다 붙이기
		for (l = j; l <= right; l++) sorted[k++] = list[l];		
	else //뒤에꺼가 먼저 다 나갔을 경우 앞에꺼 다 붙이기
		for (l = i; l <= mid; l++) sorted[k++] = list[l];
	for (l = left; l <= right; l++) {//완성배열 옮기기
		list[l] = sorted[l];
	}
}

void merge_sort(int list[], int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(list, left, mid);
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}


// 퀵 정렬
int list[MAX_SIZE];
int n;

int partition(int list[], int left, int right) {
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];
	do {
		do {
			low++;
		} while (list[low] < pivot);
		do
			high--;
		while (list[high] > pivot);
		if (low < high) Swap(list[low], list[high], temp);
		
	} while (low < high);

	Swap(list[left], list[high], temp);
	return high;
}

void quick_sort(int list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}


// 기수 정렬
#define BUCKETS 10
#define DIGITS 4
#define MAX_QUEUE_SIZE 100
typedef int element;

typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void init_queue(QueueType* q) {
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

int is_full(QueueType* q) {
	return ((q->front + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item) {
	if (is_full(q)) return;
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front] = item;
}

element dequeue(QueueType* q) {
	if (is_empty(q)) return;
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

void radix_sort(int list[], int n) {
	int i, b, d, factor = 1;
	QueueType* queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++) init_queue(&queues[b]);

	for (d = 0; d < DIGITS; d++) {
		for (i = 0; i < n; i++) enqueue(&queues[(list[i] / factor) % 10], list[i]);
		for (b = i = 0; b < BUCKETS; b++) {
			while (!is_empty(&queues[b])) {
				list[i++] = dequeue(&queues[b]);
			}
		}
		factor *= 10;
	}
}