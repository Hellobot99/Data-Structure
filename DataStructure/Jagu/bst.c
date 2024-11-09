#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;
typedef struct stackNode {
	TreeNode* tNode;
	struct stackNode* next;
} stackNode;
typedef struct queueNode {
	TreeNode* tNode;
	struct queueNode* next;
} queueNode;
typedef struct Queue {
	queueNode* front, * rear;
} Queue;

stackNode* createStack();
int isEmptyStack(stackNode* top);
void push(stackNode** top, TreeNode* tNode);
void deleteStack(stackNode** top);
TreeNode* pop(stackNode** top);

TreeNode* createNode(int data);
TreeNode* insertNode(TreeNode* root, int data);// BST에 노드를 삽입하는 함수
TreeNode* searchNode(TreeNode* root, int data);// BST에서 특정 값을 탐색하는 함수
TreeNode* findMin(TreeNode* root);// BST에서 최소값을 찾는 함수 
TreeNode* deleteNode(TreeNode* root, int data);// BST에서 노드를 삭제하는 함수

Queue* createQueue();
queueNode* createQueueNode(TreeNode* tNode);
int isEmptyQueue(Queue* q);
void enqueue(Queue* q, TreeNode* tNode);
TreeNode* dequeue(Queue* q);
void deleteQueue(Queue* q);

void Postorder_iter(TreeNode* root);
void Inorder_iter(TreeNode* root);
void Preorder_iter(TreeNode* root);
void Postorder_rec(TreeNode* root);
void Inorder_rec(TreeNode* root);
void Preorder_rec(TreeNode* root);
void Levelorder_iter(TreeNode* root);

int main() {
	srand(time(NULL));
	TreeNode* root = NULL;
	/*
	root = insertNode(root, 18);
	insertNode(root, 7);
	insertNode(root, 26);
	insertNode(root, 3);
	insertNode(root, 12);
	insertNode(root, 31);
	insertNode(root, 27);

	printf("Level order Traversal: ");
	Levelorder_iter(root);
	printf("\n");

	printf("Inorder Traversal: ");
	Inorder_rec(root);
	printf("\n");
	*/

	//과제 2번 시작
	int check[21] = { 0 };
	int random = rand() % 19 + 1;
	for (int i = 0; i < random; i++) {
		int num = rand() % 19 + 1;
		if (check[num]) {
			i++;
			continue;
		}
		else {
			check[num]++;
			if (i == 0) root = insertNode(root, num);
			else insertNode(root, num);
		}
	}
	printf("Level order Traversal: ");
	Levelorder_iter(root);
	printf("\n");

	printf("Inorder Traversal: ");
	Inorder_rec(root);
	printf("\n");

	return 0;
}

stackNode* createStack() {
	return NULL;
}
int isEmptyStack(stackNode* top) {
	return (top == NULL); // 스택이 비었으면 1 을 반환, 그렇지 않으면 0 을 반환
}
void push(stackNode** top, TreeNode* tNode) {
	stackNode* newNode = (stackNode*)malloc(sizeof(stackNode));
	if (!newNode) {
		printf("메모리 할당 실패\n");
		return;
	}
	newNode->tNode = tNode;
	newNode->next = *top;
	*top = newNode;
}
void deleteStack(stackNode** top) {
	stackNode* temp;
	while (*top) {
		temp = *top;
		*top = (*top)->next;
		free(temp);
	}
}
TreeNode* pop(stackNode** top) {
	if (isEmptyStack(*top)) {
		printf("스택이 비어 있습니다\n");
		return NULL;
	}
	stackNode* temp = *top;
	TreeNode* poppedNode = temp->tNode;
	*top = temp->next;
	free(temp);
	return poppedNode;
}

void Postorder_iter(TreeNode* root) {
	stackNode* top;
	top = createStack();
	TreeNode* last = NULL;
	while (1) {
		while (root) {
			push(&top, root);
			root = root->left;
		}//제일 왼쪽 밑까지 내려가기
		if (isEmptyStack(top))
			break;
		root = pop(&top);//왼쪽 자식이 더 이상없으니 다시 위로 한칸
		if (root->right && last != root->right) {//오른쪽 자식 출력하고 올라와서다시 내려갈수도 있으니
			push(&top, root);//오른쪽 자식이 있다면 오른쪽 자식이 먼저출력되야 하니 다시 스택에 넣음
			root = root->right;//오른쪽 자식으로 이동
		}
		else {
			printf("%d ", root->data);
			last = root;
			root = NULL; //출력 후에 while(root)문으로 다시 들어가 이미 출력된게 다시 스택에 들어가는것을 방지
		}
	}
	deleteStack(&top);
}
void Inorder_iter(TreeNode* root) {
	stackNode* top;
	top = createStack();
	while (1) {
		while (root) {
			push(&top, root);
			root = root->left;
		}//왼쪽 끝까지 내려감
		if (isEmptyStack(top))
			break;
		root = pop(&top);//스택 젤 위에 있는걸 꺼내서 출력
		printf("%d ", root->data);
		//왼쪽 중간 했으니 오른쪽 자식 있으면 오른쪽 자식으로
		if (root->right) root = root->right;
		else root = NULL;
	}
	deleteStack(&top);
}
void Preorder_iter(TreeNode* root) {
	stackNode* top;
	top = createStack();
	while (1) {
		while (root) {
			printf("%d ", root->data);
			push(&top, root);
			root = root->left;
		}//중간 부터 출력이라서 스택에 넣으면서 출력까지 왼쪽 끝까지
		if (isEmptyStack(top))
			break;
		//왼쪽 끝까지 출력했으니 올라가면서 오른쪽 자식 트리까지 확인
		root = pop(&top);
		root = root->right;
	}
	deleteStack(&top);
}
void Postorder_rec(TreeNode* root) {
	if (root->left) Postorder_rec(root->left);
	if (root->right) Postorder_rec(root->right);
	printf("%d ", root->data);
}
void Inorder_rec(TreeNode* root) {
	if (root->left) Inorder_rec(root->left);
	printf("%d ", root->data);
	if (root->right) Inorder_rec(root->right);
}
void Preorder_rec(TreeNode* root) {
	if (root) {
		printf("%d ", root->data);
		Preorder_rec(root->left);
		Preorder_rec(root->right);
	}
}
void Levelorder_iter(TreeNode* root) {
	Queue* q = createQueue();
	if (!root)
		return;

	enqueue(q, root);

	while (!isEmptyQueue(q)) {
		root = dequeue(q);
		printf("%d ", root->data);

		if (root->left)
			enqueue(q, root->left);

		if (root->right)
			enqueue(q, root->right);
	}
	deleteQueue(q);
}

TreeNode* createNode(int data) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	if (!newNode) {
		printf("메모리 할당 실패\n");
		return NULL;
	}
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}
TreeNode* insertNode(TreeNode* root, int data) {
	if (root == NULL) {
		// 새로운 노드를 반환 (루트가 비었을 때)
		return createNode(data);
	}

	if (data < root->data) {
		// 왼쪽 서브트리에 삽입
		root->left = insertNode(root->left, data);
	}
	else if (data > root->data) {
		// 오른쪽 서브트리에 삽입
		root->right = insertNode(root->right, data);
	}

	return root;
}
TreeNode* searchNode(TreeNode* root, int data) {
	if (root == NULL || root->data == data) {
		return root; // 값을 찾았거나 노드가 없으면 반환
	}

	if (data < root->data) {
		return searchNode(root->left, data); // 왼쪽 서브트리 탐색
	}
	else {
		return searchNode(root->right, data); // 오른쪽 서브트리 탐색
	}
}
TreeNode* findMin(TreeNode* root) {
	while (root->left != NULL) {
		root = root->left; // 왼쪽 끝까지 가면 최소값
	}
	return root;
}
TreeNode* deleteNode(TreeNode* root, int data) {
	if (root == NULL) {
		return root;
	}

	if (data < root->data) {
		// 왼쪽 서브트리에서 삭제
		root->left = deleteNode(root->left, data);
	}
	else if (data > root->data) {
		// 오른쪽 서브트리에서 삭제
		root->right = deleteNode(root->right, data);
	}
	else {
		// 노드를 찾았을 때
		if (root->left == NULL) {
			// 자식이 하나이거나 없는 경우
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}

		// 자식이 둘인 경우: 오른쪽 서브트리의 최소값을 찾음
		TreeNode* temp = findMin(root->right);
		root->data = temp->data; // 현재 노드를 대체
		root->right = deleteNode(root->right, temp->data); // 최소값 노드를 삭제
	}

	return root;
}

Queue* createQueue() {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	if (!q) {
		printf("메모리 할당 실패\n");
		return NULL;
	}
	q->front = q->rear = NULL;
	return q;
}
queueNode* createQueueNode(TreeNode* tNode) {
	queueNode* newNode = (queueNode*)malloc(sizeof(queueNode));
	if (!newNode) {
		printf("메모리 할당 실패\n");
		return NULL;
	}
	newNode->tNode = tNode;
	newNode->next = NULL;
	return newNode;
}
int isEmptyQueue(Queue* q) {
	return (q->front == NULL);
}
void enqueue(Queue* q, TreeNode* tNode) {
	queueNode* newNode = createQueueNode(tNode);
	if (!newNode) return;

	if (q->rear) {
		q->rear->next = newNode;
	}
	q->rear = newNode;

	if (q->front == NULL) {
		q->front = newNode;
	}
}
TreeNode* dequeue(Queue* q) {
	if (isEmptyQueue(q)) {
		printf("큐가 비어 있습니다\n");
		return NULL;
	}
	queueNode* temp = q->front;
	TreeNode* tNode = temp->tNode;
	q->front = q->front->next;
	if (q->front == NULL) {
		q->rear = NULL;
	}
	free(temp);
	return tNode;
}
void deleteQueue(Queue* q) {
	queueNode* temp;
	while (q->front) {
		temp = q->front;
		q->front = q->front->next;
		free(temp);
	}
	free(q);
}