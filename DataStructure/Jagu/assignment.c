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

int height(TreeNode* N) {
    if (N == NULL)
        return 0;
    return N->height;
}
TreeNode* create_AVL_Node(int data) {
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


int find(int* arr, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) return 1;  // 값을 찾으면 1 반환
    }
    return 0;  // 값을 찾지 못하면 0 반환
}

int main() {
    srand(time(NULL));
    int ran;
    double insert_time, search_time;
    double Ls_insert[20], Ls_search[20], Bst_insert[20], Bst_search[20], Avl_insert[20],Avl_search[20];

    
    // n이 500,000부터 10,000,000까지 500,000씩 증가
    for (int n = 500000; n <= 10000000; n += 500000) {
        // 0. n개의 랜덤한 정수 발생 후 저장
        int* list = (int*)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++) {
            list[i] = rand() * rand();
        }

        // 1. 배열에 삽입하는 시간 측정
        clock_t start = clock();
        int* arr = (int*)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++) {
            arr[i] = list[i];
        }
        clock_t end = clock();
        Ls_insert[n / 500000 - 1] = (double)(end - start) / CLOCKS_PER_SEC;

        // 2. 랜덤값을 선택하고 배열에서 찾는 시간 측정 
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

        // 1. 배열에 삽입하는 시간 측정
        for (int i = 0; i < n; i++) {
            bst = insertBSTNode(bst, list[i]);
        }

        end = clock();
        Bst_insert[n / 500000 - 1] = (double)(end - start) / CLOCKS_PER_SEC;

        // 2. 랜덤값을 선택하고 BST에서 찾는 시간 측정
        Bst_search[n / 500000 - 1] = 0;
        for (int i = 0; i < 100000; i++) {
            ran = rand() * rand();  // 이미 생성된 랜덤값 중 하나 선택
            start = clock();

            searchNode_rec(bst, ran);

            end = clock();
            Bst_search[n / 500000 - 1] += (double)(end - start) / CLOCKS_PER_SEC;
        }

        Bst_search[n / 500000 - 1] /= 100000;


        //C. AVL
        // 1. 배열에 삽입하는 시간 측정   

        TreeNode* avl = NULL;
        start = clock();
        for (int i = 0; i < n; i++) {
            insert_AVL(avl, list[i]);
        }

        end = clock();
        Avl_insert[n / 500000 - 1] = (double)(end - start) / CLOCKS_PER_SEC;

        // 2. 랜덤값을 선택하고 배열에서 찾는 시간 측정
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

    //결과 출력

    printf("A. Linear Search\n");
    for (int i = 0; i < 20; i++) {
        printf("#%d 삽입 시간 : %lf 초, 평균 찾는 시간 : %.10lf 초\n", i + 1, Ls_insert[i], Ls_search[i]);
    }
    printf("\nB. BST\n");
    for (int i = 0; i < 20; i++) {
        printf("#%d 삽입 시간 : %lf 초, 평균 찾는 시간 : %.10lf 초\n", i + 1, Bst_insert[i], Bst_search[i]);
    }
    printf("\nC. AVL\n");
    for (int i = 0; i < 20; i++) {
        printf("#%d 삽입 시간 : %lf 초, 평균 찾는 시간 : %.10lf 초\n", i + 1, Avl_insert[i], Avl_search[i]);
    }


    return 0;
}