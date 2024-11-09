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

int main() {

}