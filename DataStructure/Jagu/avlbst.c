#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define max(x, y) ((x) > (y) ? (x) : (y))

typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
	int height;
} TreeNode;
TreeNode* createBSTNode(int data) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	if (!newNode) {
		printf("�޸� �Ҵ� ����\n");
		return NULL;
	}
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	newNode->height = 0;
	return newNode;
}
TreeNode* insertBSTNode(TreeNode* root, int data) {
	if (root == NULL) {
		// ���ο� ��带 ��ȯ (��Ʈ ���� ���� ��)
		return createBSTNode(data);
	}
	if (data < root->data) {
		root->left = insertBSTNode(root->left, data);
		//���ο� ��� ���� ���ʿ� ���̱�
	}
	else if (data > root->data) {
		root->right = insertBSTNode(root->right, data);
		//���ο� ��� ���� �����ʿ� ���̱�
	}
	else return root;
	return root;
}
TreeNode* searchNode_rec(TreeNode* root, int data) {//(��Ʈ�ּ�,ã������ ��)
	if (root == NULL || root->data == data) {
		return root; // ���� ã�Ұų� ��尡 ������ ��ȯ
	}
	if (data < root->data) { //����ִ� ������ ���� ���
		return searchNode_rec(root->left, data); // ���� ���� �������� Ž��
	}
	else { // ����ִ� ������ Ŭ ���
		return searchNode_rec(root->right, data); // ������ ���� �������� Ž��
	}
}
TreeNode* searchNode_iter(TreeNode* root, int data, int* try_num) {
	*try_num = 0;
	while (root != NULL) { // ��忡 �ƹ��͵� ������ ���� (�ǹ� ����)
		(*try_num)++;
		if (data == root->data) return root; //���� ã���� ��ȯ
		else if (data < root->data) root = root->left; //���� ��� ��������
		else root = root->right; // Ŭ ��� ����������
	}
	(*try_num) = 0;
	return NULL;//Ž�� ���� �� NULL ����
}
// �� ��� ����
TreeNode* createNode(int data) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	if (!newNode) {
		printf("�޸� �Ҵ� ����\n");
		return NULL;
	}
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	newNode->height = 0;
	return newNode;
}
// ����� ���� ��ȯ
int height(TreeNode* N) {
	if (N == NULL)
		return 0;
	return N->height;
}
// ������ ȸ��
TreeNode* rightRotate(TreeNode* x) {
	TreeNode* w = x->left;
	x->left = w->right;
	w->right = x;
	x->height = max(height(x->left), height(x->right)) + 1;
	w->height = max(height(w->left), height(w->right)) + 1;

	return w;
}
// ���� ȸ��
TreeNode* leftRotate(TreeNode* x) {
	TreeNode* w = x->right;
	x->right = w->left;
	w->left = x;
	x->height = max(height(x->left), height(x->right)) + 1;
	w->height = max(height(w->left), height(w->right)) + 1;
	return w;

}
// ���� �μ� ��ȯ
int getBalance(TreeNode* N) {
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}
// AVL Ʈ���� ��� ����
TreeNode* insert_AVL(TreeNode* node, int data) {
	if (node == NULL)
		return createNode(data);
	if (data < node->data)
		node->left = insert_AVL(node->left, data);
	else if (data > node->data)
		node->right = insert_AVL(node->right, data);
	else
		return node; // �ߺ��� �����ʹ� �������� ����
	// ����� ���� ������Ʈ
	node->height = 1 + max(height(node->left), height(node->right));
	// ����� ���� ���
	int balance = getBalance(node);
	// ������ ���� �ʴٸ� ȸ�� ����
	// Left Left Case
	if (balance > 1 && data < node->left->data) {
		return rightRotate(node);
	}
	// Right Right Case
	if (balance < -1 && data > node->right->data) {
		return leftRotate(node);
	}
	// Left Right Case
	if (balance > 1 && data > node->left->data) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	// Right Left Case
	if (balance < -1 && data < node->right->data) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node; // ������ Ʈ���� ��Ʈ�� ��ȯ
}

TreeNode* findMin(TreeNode* root) {
	while (root->left != NULL) {
		root = root->left; // ���� ������ ���� �ּҰ�
	}
	return root;
}

// AVL Ʈ������ ��� ����
TreeNode* delete_AVL(TreeNode* root, int data) {
	if (root == NULL)
		return root;

	// Ʈ������ �����͸� ã��
	if (data < root->data)
		root->left = delete_AVL(root->left, data);
	else if (data > root->data)
		root->right = delete_AVL(root->right, data);
	else {
		// ������ ��带 ã���� ��
		// �ڽ��� �ϳ� �ų� ���� ��
		if ((root->left == NULL) || (root->right == NULL)) {
			TreeNode* temp = root->left ? root->left : root->right;//root�� ���� �ڽ��� �����ϸ� temp�� root->left��, �׷��� ������ root->right�� �Ҵ�
			//�ڽ��� ���� ��
			if (temp == NULL) {
				temp = root;
				root = NULL;
			}
			//�ڽ��� �ϳ� ���� ��
			else 
				*root = *temp; //������ �ڽĳ��� ��ü
			free(temp);
		}
		else {
			// �� ���� �ڽ��� ���� ����� ���
			// �ڽ��� ���� ���: ������ ����Ʈ���� �ּҰ��� ã��
			TreeNode* temp = findMin(root->right);
			root->data = temp->data; // ���� ��带 ��ü
			root->right = delete_AVL(root->right, temp->data); // �ּҰ� ��带 ����
		}
	}

	// Ʈ���� NULL�� �� ��� ��ȯ
	if (root == NULL)
		return root;

	// ����� ���� ������Ʈ
	root->height = 1 + max(height(root->left), height(root->right));

	// ���� �μ� ���
	int balance = getBalance(root);

	// �ұ��� �ذ�
	// Left Left Case
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	// Left Right Case
	if (balance > 1 && getBalance(root->left) < 0) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Right Case
	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	// Right Left Case
	if (balance < -1 && getBalance(root->right) > 0) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}


void inOrder(TreeNode* root) {
	if (root != NULL) {
		inOrder(root->left);
		printf("%d ", root->data);
		inOrder(root->right);
	}
}

int main() {
	

	return 0;
}