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
		printf("메모리 할당 실패\n");
		return NULL;
	}
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	newNode->height = 0;
	return newNode;
}
TreeNode* insertBSTNode(TreeNode* root, int data) {
	if (root == NULL) {
		// 새로운 노드를 반환 (루트 최초 생성 시)
		return createBSTNode(data);
	}
	if (data < root->data) {
		root->left = insertBSTNode(root->left, data);
		//새로운 노드 만들어서 왼쪽에 붙이기
	}
	else if (data > root->data) {
		root->right = insertBSTNode(root->right, data);
		//새로운 노드 만들어서 오른쪽에 붙이기
	}
	else return root;
	return root;
}
TreeNode* searchNode_rec(TreeNode* root, int data) {//(루트주소,찾으려는 값)
	if (root == NULL || root->data == data) {
		return root; // 값을 찾았거나 노드가 없으면 반환
	}
	if (data < root->data) { //들어있는 값보다 작을 경우
		return searchNode_rec(root->left, data); // 왼쪽 으로 내려가서 탐색
	}
	else { // 들어있는 값보다 클 경우
		return searchNode_rec(root->right, data); // 오른쪽 으로 내려가서 탐색
	}
}
TreeNode* searchNode_iter(TreeNode* root, int data, int* try_num) {
	*try_num = 0;
	while (root != NULL) { // 노드에 아무것도 없을때 까지 (맨및 까지)
		(*try_num)++;
		if (data == root->data) return root; //값을 찾으면 반환
		else if (data < root->data) root = root->left; //작을 경우 왼쪽으로
		else root = root->right; // 클 경우 오른쪽으로
	}
	(*try_num) = 0;
	return NULL;//탐색 실패 시 NULL 리턴
}
// 새 노드 생성
TreeNode* createNode(int data) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	if (!newNode) {
		printf("메모리 할당 실패\n");
		return NULL;
	}
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	newNode->height = 0;
	return newNode;
}
// 노드의 높이 반환
int height(TreeNode* N) {
	if (N == NULL)
		return 0;
	return N->height;
}
// 오른쪽 회전
TreeNode* rightRotate(TreeNode* x) {
	TreeNode* w = x->left;
	x->left = w->right;
	w->right = x;
	x->height = max(height(x->left), height(x->right)) + 1;
	w->height = max(height(w->left), height(w->right)) + 1;

	return w;
}
// 왼쪽 회전
TreeNode* leftRotate(TreeNode* x) {
	TreeNode* w = x->right;
	x->right = w->left;
	w->left = x;
	x->height = max(height(x->left), height(x->right)) + 1;
	w->height = max(height(w->left), height(w->right)) + 1;
	return w;

}
// 균형 인수 반환
int getBalance(TreeNode* N) {
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}
// AVL 트리에 노드 삽입
TreeNode* insert_AVL(TreeNode* node, int data) {
	if (node == NULL)
		return createNode(data);
	if (data < node->data)
		node->left = insert_AVL(node->left, data);
	else if (data > node->data)
		node->right = insert_AVL(node->right, data);
	else
		return node; // 중복된 데이터는 삽입하지 않음
	// 노드의 높이 업데이트
	node->height = 1 + max(height(node->left), height(node->right));
	// 노드의 균형 계산
	int balance = getBalance(node);
	// 균형이 맞지 않다면 회전 수행
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
	return node; // 수정된 트리의 루트를 반환
}

TreeNode* findMin(TreeNode* root) {
	while (root->left != NULL) {
		root = root->left; // 왼쪽 끝까지 가면 최소값
	}
	return root;
}

// AVL 트리에서 노드 삭제
TreeNode* delete_AVL(TreeNode* root, int data) {
	if (root == NULL)
		return root;

	// 트리에서 데이터를 찾음
	if (data < root->data)
		root->left = delete_AVL(root->left, data);
	else if (data > root->data)
		root->right = delete_AVL(root->right, data);
	else {
		// 삭제할 노드를 찾았을 때
		// 자식이 하나 거나 없을 때
		if ((root->left == NULL) || (root->right == NULL)) {
			TreeNode* temp = root->left ? root->left : root->right;//root의 왼쪽 자식이 존재하면 temp에 root->left를, 그렇지 않으면 root->right를 할당
			//자식이 없을 때
			if (temp == NULL) {
				temp = root;
				root = NULL;
			}
			//자식이 하나 있을 때
			else 
				*root = *temp; //본인을 자식노드로 대체
			free(temp);
		}
		else {
			// 두 개의 자식을 가진 노드의 경우
			// 자식이 둘인 경우: 오른쪽 서브트리의 최소값을 찾음
			TreeNode* temp = findMin(root->right);
			root->data = temp->data; // 현재 노드를 대체
			root->right = delete_AVL(root->right, temp->data); // 최소값 노드를 삭제
		}
	}

	// 트리가 NULL이 된 경우 반환
	if (root == NULL)
		return root;

	// 노드의 높이 업데이트
	root->height = 1 + max(height(root->left), height(root->right));

	// 균형 인수 계산
	int balance = getBalance(root);

	// 불균형 해결
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