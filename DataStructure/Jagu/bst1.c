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
TreeNode* insertNode(TreeNode* root, int data);// BST�� ��带 �����ϴ� �Լ�
TreeNode* searchNode(TreeNode* root, int data);// BST���� Ư�� ���� Ž���ϴ� �Լ�
TreeNode* findMin(TreeNode* root);// BST���� �ּҰ��� ã�� �Լ� 
TreeNode* deleteNode(TreeNode* root, int data);// BST���� ��带 �����ϴ� �Լ�

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

	//���� 2�� ����
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
	return (top == NULL); // ������ ������� 1 �� ��ȯ, �׷��� ������ 0 �� ��ȯ
}
void push(stackNode** top, TreeNode* tNode) {
	stackNode* newNode = (stackNode*)malloc(sizeof(stackNode));
	if (!newNode) {
		printf("�޸� �Ҵ� ����\n");
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
		printf("������ ��� �ֽ��ϴ�\n");
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
		}//���� ���� �ر��� ��������
		if (isEmptyStack(top))
			break;
		root = pop(&top);//���� �ڽ��� �� �̻������ �ٽ� ���� ��ĭ
		if (root->right && last != root->right) {//������ �ڽ� ����ϰ� �ö�ͼ��ٽ� ���������� ������
			push(&top, root);//������ �ڽ��� �ִٸ� ������ �ڽ��� ������µǾ� �ϴ� �ٽ� ���ÿ� ����
			root = root->right;//������ �ڽ����� �̵�
		}
		else {
			printf("%d ", root->data);
			last = root;
			root = NULL; //��� �Ŀ� while(root)������ �ٽ� �� �̹� ��µȰ� �ٽ� ���ÿ� ���°��� ����
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
		}//���� ������ ������
		if (isEmptyStack(top))
			break;
		root = pop(&top);//���� �� ���� �ִ°� ������ ���
		printf("%d ", root->data);
		//���� �߰� ������ ������ �ڽ� ������ ������ �ڽ�����
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
		}//�߰� ���� ����̶� ���ÿ� �����鼭 ��±��� ���� ������
		if (isEmptyStack(top))
			break;
		//���� ������ ��������� �ö󰡸鼭 ������ �ڽ� Ʈ������ Ȯ��
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
		printf("�޸� �Ҵ� ����\n");
		return NULL;
	}
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}
TreeNode* insertNode(TreeNode* root, int data) {
	if (root == NULL) {
		// ���ο� ��带 ��ȯ (��Ʈ�� ����� ��)
		return createNode(data);
	}

	if (data < root->data) {
		// ���� ����Ʈ���� ����
		root->left = insertNode(root->left, data);
	}
	else if (data > root->data) {
		// ������ ����Ʈ���� ����
		root->right = insertNode(root->right, data);
	}

	return root;
}
TreeNode* searchNode(TreeNode* root, int data) {
	if (root == NULL || root->data == data) {
		return root; // ���� ã�Ұų� ��尡 ������ ��ȯ
	}

	if (data < root->data) {
		return searchNode(root->left, data); // ���� ����Ʈ�� Ž��
	}
	else {
		return searchNode(root->right, data); // ������ ����Ʈ�� Ž��
	}
}
TreeNode* findMin(TreeNode* root) {
	while (root->left != NULL) {
		root = root->left; // ���� ������ ���� �ּҰ�
	}
	return root;
}
TreeNode* deleteNode(TreeNode* root, int data) {
	if (root == NULL) {
		return root;
	}

	if (data < root->data) {
		// ���� ����Ʈ������ ����
		root->left = deleteNode(root->left, data);
	}
	else if (data > root->data) {
		// ������ ����Ʈ������ ����
		root->right = deleteNode(root->right, data);
	}
	else {
		// ��带 ã���� ��
		if (root->left == NULL) {
			// �ڽ��� �ϳ��̰ų� ���� ���
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}

		// �ڽ��� ���� ���: ������ ����Ʈ���� �ּҰ��� ã��
		TreeNode* temp = findMin(root->right);
		root->data = temp->data; // ���� ��带 ��ü
		root->right = deleteNode(root->right, temp->data); // �ּҰ� ��带 ����
	}

	return root;
}

Queue* createQueue() {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	if (!q) {
		printf("�޸� �Ҵ� ����\n");
		return NULL;
	}
	q->front = q->rear = NULL;
	return q;
}
queueNode* createQueueNode(TreeNode* tNode) {
	queueNode* newNode = (queueNode*)malloc(sizeof(queueNode));
	if (!newNode) {
		printf("�޸� �Ҵ� ����\n");
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
		printf("ť�� ��� �ֽ��ϴ�\n");
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