#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
    int height;
} TreeNode;

// ����� ���� ��ȯ
int height(TreeNode* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// �� ��� ����
TreeNode* createNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // �� ��� ���� �� ���̴� 1
    return node;
}

// ���ο� �� Ʈ�� ����
TreeNode* createTree() { 
    return NULL; // �� Ʈ���� ��� NULL ��ȯ
}

// ���� ȸ��
TreeNode* leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* z = y->left;

    // ȸ�� ����
    y->left = x;
    x->right = z;

    // ���� ������Ʈ
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // ���ο� ��Ʈ ��ȯ
    return y;
}
// ������ ȸ��
TreeNode* rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* z = x->right;

    // ȸ�� ����
    x->right = y;
    y->left = z;

    // ���� ������Ʈ
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // ���ο� ��Ʈ ��ȯ
    return x;
}
// ���� ��� ���
int getBalance(TreeNode* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// AVL Ʈ���� �� ������ ����
TreeNode* insert(TreeNode* node, int data) {
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node; // �ߺ��� �����ʹ� �������� ����

    // ����� ���� ������Ʈ
    node->height = 1 + max(height(node->left), height(node->right));

    // ����� ���� ��� ���
    int balance = getBalance(node);

    // ������ ���� �ʴٸ� ȸ�� ����

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

    return node; // ������ Ʈ���� ��Ʈ�� ��ȯ
}

// ���� ��ȸ
void inOrder(TreeNode* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

int main() {
    TreeNode* root = createTree(); // �� Ʈ�� ����

    // AVL Ʈ���� ������ ����
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    // ���� ��ȸ�� Ʈ�� ���
    printf("���� ��ȸ ���: ");
    inOrder(root);

    return 0;
}
