#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define max(x, y) ((x) > (y) ? (x) : (y))
int how_many = 0;

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
    int height;
} TreeNode;

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

int main() {

}