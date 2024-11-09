#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class BSTNode {
public:
    int value;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int value) : value(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {   

public:
    BSTNode* root;
    BinarySearchTree() : root(nullptr) {}

    void insert(int value);
    bool search(int value);
    void remove(int value);
    void inorderTraversal(BSTNode* node);


    BSTNode* getRoot() {
        return root;
    }
};

void BinarySearchTree::insert(int value) {
    if (!root) {
        root = new BSTNode(value);
        return;
    }
    BSTNode* current = root;
    BSTNode* parent = nullptr;
    while (current) {
        parent = current;
        if (current->value == value) {
            return;
        }
        else if (current->value < value) {
            current = current->right;
        }
        else {
            current = current->left;
        }
    }
    BSTNode* newnode = new BSTNode(value);

    if (parent->value < value) {
        parent->right = newnode;
    }
    else {
        parent->left = newnode;
    }
    return;
}

bool BinarySearchTree::search(int value) {
    if (!root) {
        return false;
    }
    BSTNode* current = root;

    while (current) {
        if (current->value > value) {
            current = current->left;
        }
        else if (current->value < value) {
            current = current->right;
        }
        else {
            return true;
        }
    }
    if (!current) return false;
}

void BinarySearchTree::remove(int value) {
    if (!root) {
        return;
    }
    BSTNode* current = root;

    while (current) {

        if (current->value > value) {
            current = current->left;
        }
        else if (current->value < value) {
            current = current->right;
        }
        else {
            break;
        }
    }

    if (!current) return;

    BSTNode* tmp = current;

    if (!current->left && !current->right) {
        delete current;
    }
    else if (!(current->left)) { //왼쪽 오른쪽 둘다 없거나 오른쪽만 있을때
        tmp = current->right;
        delete current->right;
        current = tmp; 
        
    }
    else if (!(current->right)) { // 왼쪽만 있을때
        current->value = current->left->value;
        delete current->left;
    }
    else {//둘다 있을때
        BSTNode* parent = current;
        BSTNode* change = current->left;
        while (change->right) {
            parent = change;
            change = change->right;
        }

        current->value = change->value;
        if (current->left) parent->right = current->left;
        else current = nullptr;
        
    }
}

void BinarySearchTree::inorderTraversal(BSTNode* rootValue) {
    if (rootValue) {
        inorderTraversal(rootValue->left);
        cout << rootValue->value << " ";
        inorderTraversal(rootValue->right);
    }
    
}

int main() {
    BinarySearchTree bst;

    // 노드 추가
    bst.insert(50);
    bst.insert(30);
    bst.insert(20);
    bst.insert(40);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);

    cout << "In-order Traversal of the BST before removal:\n";
    bst.inorderTraversal(bst.root);
    cout << endl;

    // 노드 삭제
    bst.remove(20); // 리프 노드 삭제
    cout << "In-order Traversal after removing 20:\n";
    bst.inorderTraversal(bst.root);
    cout << endl;

    bst.remove(30); // 한 개의 자식 노드 삭제
    cout << "In-order Traversal after removing 30:\n";
    bst.inorderTraversal(bst.root);
    cout << endl;

    bst.remove(50); // 두 개의 자식 노드 삭제 (루트 삭제)
    cout << "In-order Traversal after removing 50:\n";
    bst.inorderTraversal(bst.root);
    cout << endl;

    return 0;
}