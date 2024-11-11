#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;


Node* createNode(int data) {
    Node* new = (Node*)malloc(sizeof(Node));
    new->data = data;
    new->left = new->right = NULL;
}

Node* insertBST(Node* root, int data) {
    if(!root) return createNode(data);

    if (root->data > data) root->left = insertBST(root->left, data);
    else if (root->data < data) root->right = insertBST(root->right, data);

    return root;        
}

Node* deleteBST(Node* root, int data) {
    Node* temp;
    if (!root) return NULL;
    
    if (root->data > data) root->left = deleteBST(root->left, data);
    else if (root->data < data) root->right = deleteBST(root->right, data);
    else {
        if (!root->left && !root->right) {
            free(root);
            return NULL;
        }
        else if (!root->left) {
            temp = root->right;
            free(root);
            return temp;
        }
        else if (!root->right) {
            temp = root->left;
            free(root);
            return temp;
        }
        else {
            temp = root->left;
            while (temp->right) {
                temp = temp->right;
            }
            root->data = temp->data;
            root->left = deleteBST(root->left, temp->data);
        }
    }   
    return root;
}

Node* searchBST(Node* root, int data) {
    Node* temp = root;
    while (temp) {
        if (temp->data > data) temp = temp->left;
        else if (temp->data < data) temp = temp->right;
        else return temp;
    }
    return NULL;
}

void preorderTraversal(Node* root) {
    if (root) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void inorderTraversal(Node* root) {
    if (root) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

void postorderTraversal(Node* root) {
    if (root) {        
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

void freeTree(Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {

    Node* root = NULL;

    root = insertBST(root, 10);
    root = insertBST(root, 5);
    root = insertBST(root, 15);
    root = insertBST(root, 2);
    root = insertBST(root, 7);

    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    Node* found = searchBST(root, 7);
    if (found != NULL) {
        printf("Found node with data: %d\n", found->data);
    }
    else {
        printf("Node with data 7 not found.\n");
    }

    root = deleteBST(root, 10);

    printf("Inorder Traversal after deletion: ");
    inorderTraversal(root);
    printf("\n");

    freeTree(root);

    return 0;
}
