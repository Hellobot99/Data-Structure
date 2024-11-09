#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
    int height;
} TreeNode;

// 노드의 높이 반환
int height(TreeNode* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// 새 노드 생성
TreeNode* createNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // 새 노드 삽입 시 높이는 1
    return node;
}

// 새로운 빈 트리 생성
TreeNode* createTree() { 
    return NULL; // 빈 트리의 경우 NULL 반환
}

// 왼쪽 회전
TreeNode* leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* z = y->left;

    // 회전 수행
    y->left = x;
    x->right = z;

    // 높이 업데이트
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // 새로운 루트 반환
    return y;
}
// 오른쪽 회전
TreeNode* rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* z = x->right;

    // 회전 수행
    x->right = y;
    y->left = z;

    // 높이 업데이트
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // 새로운 루트 반환
    return x;
}
// 균형 계수 계산
int getBalance(TreeNode* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// AVL 트리에 새 데이터 삽입
TreeNode* insert(TreeNode* node, int data) {
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node; // 중복된 데이터는 삽입하지 않음

    // 노드의 높이 업데이트
    node->height = 1 + max(height(node->left), height(node->right));

    // 노드의 균형 계수 계산
    int balance = getBalance(node);

    // 균형이 맞지 않다면 회전 수행

    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

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

// 중위 순회
void inOrder(TreeNode* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

int main() {
    TreeNode* root = createTree(); // 빈 트리 생성

    // AVL 트리에 데이터 삽입
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    // 중위 순회로 트리 출력
    printf("중위 순회 결과: ");
    inOrder(root);

    return 0;
}
