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

int height(TreeNode* N) {
    if (N == NULL)
        return 0;
    return N->height;
}
TreeNode* create_AVL_Node(int data) {
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
TreeNode* rightRotate(TreeNode* x) {
    TreeNode* w = x->left;
    x->left = w->right;
    w->right = x;
    x->height = max(height(x->left), height(x->right)) + 1;
    w->height = max(height(w->left), height(w->right)) + 1;

    return w;
}
TreeNode* leftRotate(TreeNode* x) {
    TreeNode* w = x->right;
    x->right = w->left;
    w->left = x;
    x->height = max(height(x->left), height(x->right)) + 1;
    w->height = max(height(w->left), height(w->right)) + 1;
    return w;

}
int getBalance(TreeNode* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
TreeNode* insert_AVL(TreeNode* node, int data) {
    if (node == NULL)
        return create_AVL_Node(data);
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


int find(int* arr, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) return 1;  // ���� ã���� 1 ��ȯ
    }
    return 0;  // ���� ã�� ���ϸ� 0 ��ȯ
}

int main() {
    srand(time(NULL));
    int ran;
    double insert_time, search_time;
    double Ls_insert[20], Ls_search[20], Bst_insert[20], Bst_search[20], Avl_insert[20],Avl_search[20];

    
    // n�� 500,000���� 10,000,000���� 500,000�� ����
    for (int n = 500000; n <= 10000000; n += 500000) {
        // 0. n���� ������ ���� �߻� �� ����
        int* list = (int*)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++) {
            list[i] = rand() * rand();
        }

        // 1. �迭�� �����ϴ� �ð� ����
        clock_t start = clock();
        int* arr = (int*)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++) {
            arr[i] = list[i];
        }
        clock_t end = clock();
        Ls_insert[n / 500000 - 1] = (double)(end - start) / CLOCKS_PER_SEC;

        // 2. �������� �����ϰ� �迭���� ã�� �ð� ���� 
        Ls_search[n / 500000 - 1] = 0;
        for (int i = 0; i < 100; i++) {
            ran = rand() * rand();
            start = clock();

            find(arr, n, ran);

            end = clock();
            Ls_search[n / 500000 - 1] += (double)(end - start) / CLOCKS_PER_SEC;
        }

        Ls_search[n / 500000 - 1] /= 100;


        //B. BST
        TreeNode* bst = NULL;
        start = clock();

        // 1. �迭�� �����ϴ� �ð� ����
        for (int i = 0; i < n; i++) {
            bst = insertBSTNode(bst, list[i]);
        }

        end = clock();
        Bst_insert[n / 500000 - 1] = (double)(end - start) / CLOCKS_PER_SEC;

        // 2. �������� �����ϰ� BST���� ã�� �ð� ����
        Bst_search[n / 500000 - 1] = 0;
        for (int i = 0; i < 100000; i++) {
            ran = rand() * rand();  // �̹� ������ ������ �� �ϳ� ����
            start = clock();

            searchNode_rec(bst, ran);

            end = clock();
            Bst_search[n / 500000 - 1] += (double)(end - start) / CLOCKS_PER_SEC;
        }

        Bst_search[n / 500000 - 1] /= 100000;


        //C. AVL
        // 1. �迭�� �����ϴ� �ð� ����   

        TreeNode* avl = NULL;
        start = clock();
        for (int i = 0; i < n; i++) {
            insert_AVL(avl, list[i]);
        }

        end = clock();
        Avl_insert[n / 500000 - 1] = (double)(end - start) / CLOCKS_PER_SEC;

        // 2. �������� �����ϰ� �迭���� ã�� �ð� ����
        Avl_search[n / 500000 - 1] = 0;
        for (int i = 0; i < 100000; i++) {
            ran = rand() * rand();
            start = clock();

            searchNode_rec(avl, ran);

            end = clock();
            Avl_search[n / 500000 - 1] += (double)(end - start) / CLOCKS_PER_SEC; 
        } 

        Avl_search[n / 500000 - 1] /= 100000;

        free(arr);
        free(list);
        free(bst);
        free(avl);
    }

    //��� ���

    printf("A. Linear Search\n");
    for (int i = 0; i < 20; i++) {
        printf("#%d ���� �ð� : %lf ��, ��� ã�� �ð� : %.10lf ��\n", i + 1, Ls_insert[i], Ls_search[i]);
    }
    printf("\nB. BST\n");
    for (int i = 0; i < 20; i++) {
        printf("#%d ���� �ð� : %lf ��, ��� ã�� �ð� : %.10lf ��\n", i + 1, Bst_insert[i], Bst_search[i]);
    }
    printf("\nC. AVL\n");
    for (int i = 0; i < 20; i++) {
        printf("#%d ���� �ð� : %lf ��, ��� ã�� �ð� : %.10lf ��\n", i + 1, Avl_insert[i], Avl_search[i]);
    }


    return 0;
}