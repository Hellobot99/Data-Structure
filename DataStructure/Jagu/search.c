#include <stdio.h>
#include <stdlib.h>

// ¼øÂ÷ Å½»ö
int seq_search(int key, int low, int high, int list[]) {
	int i;

	for (i = low; i <= high; i++) {
		if (list[i] == key)return i;
	}
	return -1;
}

// ÀÌÁø Å½»ö(Àç±Í)
int search_binary(int key, int low, int high, int list[]) {
	int middle;
	if (low <= high) {
		middle = (low + high) / 2;
		if (key == list[middle]) return middle;
		else if (key < list[middle]) return search_binary(key, low, middle - 1, list);
		else return  search_binary(key, middle + 1, high, list);
	}
	return -1;
}

// ÀÌÁø Å½»ö(¹İº¹)
int search_binary2(int key, int low, int high, int list[]) {
	int middle;
	while (low <= high) {
		middle = (low + high) / 2;
		if (key == list[middle]) return middle;
		else if (key > list[middle]) low = middle + 1;
		else high = middle - 1;
	}
	return -1;
}

// »öÀÎ ¼øÂ÷ Å½»ö
#define INDEX_SIZE 256
typedef struct {
	int key;
	int index;
} itable;
itable index_list[INDEX_SIZE];

int search_index(int key, int n, int list[]) {
	int i, low, high;
	if (key<list[0] || key>list[n - 1]) return -1;
	for (i = 0; i < INDEX_SIZE; i++) {
		if (index_list[i].key <= key && index_list[i + 1].key > key) break;
		if (i == INDEX_SIZE) {
			low = index_list[i - 1].index;
			high = n;
		}
		else {
			low = index_list[i].index;
			high = index_list[i + 1].index;
		}
	}
	return seq_search(key, low, high, list);
}

int interpol_search(int key, int n, int list[]) {
	int low, high, j;
	low = 0;
	high = n - 1;
	while ((list[high]) >= key && (key > list[low])) {
		j = ((float)(key - list[low]) / (list[high] - list[low]) * (high - low)) + low;
		if (key > list[j])low = j - 1;
		else if (key < list[j]) high = j - 1;
		else low = j;
	}
	if (list[low] == key)return(low);
	else return -1;
}

