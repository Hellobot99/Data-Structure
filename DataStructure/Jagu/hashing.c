//개방 주소법 : 해쉬 충돌이 일어나면 해시 테이블의 다른 위치에 저장
// 1.선형 탐사법(Linear Probing): 충돌이 발생하면 한 칸씩 이동하면서 빈 자리를 찾는 방법.
// 2. 제곱 탐사법(Quadratic Probing): 충돌이 발생할 때 탐사 거리가 1, 4, 9...와 같이 제곱수로 증가하는 방법.
// 3. 이중 해싱(Double Hashing): 두 번째 해시 함수로 이동할 위치를 계산하는 방식.
//체이닝 : 해시테이블의 하나의 위치가 여러개의 항목을 저장할 수 있도록 구조 변경

#include <stdio.h>
#include <stdlib.h>
#define KEY_SIZE 10
#define TABLE_SIZE 13
#define TABLE_SIZE_2 11
#define empty(item) (strlen(item.key)==0)
#define equal(item1,item2)(!strcmp(item1.key,item.key))

typedef struct {
	char key[KEY_SIZE];
}element;
element hash_table[TABLE_SIZE];

typedef struct {
	element item;
	struct list* link;
}list;
list* chain_hash_table[TABLE_SIZE];

void init_table(element ht[]) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		ht[i].key[0] = NULL;
	}
}
void init_chain_table(list* ht[]);
long long transform(char* key);
int hash_function(char* key);
int hash_function2(char* key);
int hash_lp_add(element item, element ht[]);
int hash_lp_search(element item, element ht[]);
int hash_qp_add(element item, element ht[]);
int hash_dh_add(element item, element ht[]);
int hash_chain_add(element item, list* ht[]);
int hash_chain_search(element item, list* ht[]);
void hash_chain_print(list* ht[]);

int main() {
	char* s[7] = { "do", "for", "if", "case", "else", "return", "function" };
	element e;
	init_table(chain_hash_table); // 해시 테이블 초기화

	for (int i = 0; i < 7; i++) {
		strcpy(e.key, s[i]);
		hash_chain_add(e, chain_hash_table);
		hash_chain_print(chain_hash_table);
	}

	for (int i = 0; i < 7; i++) {
		strcpy(e.key, s[i]);
		if (hash_chain_search(e, chain_hash_table))
			printf("찾음\n");
		else
			printf("못찾음\n");
	}

	return 0;
}

void init_chain_table(list* ht[]) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		ht[i] = NULL;
	}
}
long long transform(char* key) {
	long long number = 0;
	while (*key)
		number = (31 * number + *key++) % 1000000007;
	return number;
}
int hash_function(char* key) {
	return transform(key) % TABLE_SIZE;
}
int hash_function2(char* key) {
	return TABLE_SIZE_2-(transform(key)%TABLE_SIZE_2);
}

int hash_lp_add(element item, element ht[]) {
	int i, hash_value;
	hash_value = i = hash_function(item.key);
	while (!empty(ht[i])) {
		if (equal(item, ht[i])) { //이미 들어가있는 거면 종료
			return 0;
		}
		i = (i + 1) % TABLE_SIZE;
		if (i == hash_value) {//자리가 없으면 종료
			return 0;
		}
	}
	ht[i] = item;
	return 1;
}
int hash_lp_search(element item, element ht[]) {
	int i, hash_value;
	hash_value = i = hash_function(item.key);
	while (!empty(ht[i])) {
		if (equal(item, ht[i])) return 0;
		i = (i + 1) % TABLE_SIZE;
		if (i == hash_value) return 1;
	}
	return 0;
}
void hash_lp_print(element ht[]) {
	printf("\n======================\n");
	for (int i = 0; i < TABLE_SIZE; i++) {
		printf("[%d] %s\n", i, ht[i].key);
	}
}
int hash_qp_add(element item, element ht[]) {
	int i, hash_value, inc = 0;
	hash_value = i = hash_function(item.key);
	while (!empty(ht[i])) { //이미 들어가있으면
		if (equal(item, ht[i])) return 0;
		i = (hash_value + inc * inc) % TABLE_SIZE;
		inc++;
		if (i == hash_value) return 0; //한바퀴 돌았는데 자리가 없을때 
	}
	ht[i] = item;
}
int hash_dh_add(element item, element ht[]) {
	int i = 0, hash_value, inc;
	hash_value = i = hash_function(item.key);
	inc = hash_function2(item.key);

	while (!empty(ht[i])) {
		if (equal(item, ht[i]))return 0;
		i = (i + inc) % TABLE_SIZE;
		if (i == hash_value) return 0;
	}
	ht[i] = item;
}

int hash_chain_add(element item, list* ht[]) {
	int hash_value = hash_function(item.key);
	
	list* node_before = NULL;
	list* node = ht[hash_value];

	while (node) {
		if (strcmp(node->item.key, item.key) == 0) return 0;
		node_before = node;
		node = node->link;
	}

	list* ptr = (list*)malloc (sizeof(list));
	ptr->item = item;
	ptr->link = NULL;

	if (node_before) node_before->link = ptr; // 기존에 노드가 있다면 그 뒤에 연결
	else ht[hash_value] = ptr; // 기존에 아무것도 없다면 해쉬 테이블에 바로 연결
}
int hash_chain_search(element item, list* ht[]) {
	list* node;
	int hash_value = hash_function(item.key);
	
	node = ht[hash_value];
	while (node) {
		if (strcmp(node->item.key, item.key) == 0) return 1;
		node = node->link;
	}
	return 0;
}
void hash_chain_print(list* ht[]) {
	list* node;
	printf("\n========================\n");
	for (int i = 0; i < TABLE_SIZE; i++) {
		printf("[%d]->", i);
		node = ht[i];
		while (node) {
			printf("%s->", node->item.key);
			node = node->link;
		}
		printf("\n");
	}
	printf("\n========================\n");
}