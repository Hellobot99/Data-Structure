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

    // 트리 삽입 예시
    insertNode(&root, 10);
    insertNode(&root, 5);
    insertNode(&root, 15);

    // 트리 순회 예시
    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    // 트리 메모리 해제
    freeTree(root);

    return 0;
}
