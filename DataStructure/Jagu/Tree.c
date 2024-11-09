#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct Node {
    element data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(element data) {

}

void insertNode(Node** root, element data);

void deleteNode(Node** root, element data);

void inorderTraversal(Node* root);
void preorderTraversal(Node* root);
void postorderTraversal(Node* root);

void freeTree(Node* root);

int main() {

    Node* root = NULL;

    // Ʈ�� ���� ����
    insertNode(&root, 10);
    insertNode(&root, 5);
    insertNode(&root, 15);

    // Ʈ�� ��ȸ ����
    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    // Ʈ�� �޸� ����
    freeTree(root);

    return 0;
}
