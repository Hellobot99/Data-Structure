#include <iostream>
#include <vector>
#include <map>
using namespace std;

class TreeNode {
public:
    int value;
    TreeNode(int value);
    TreeNode();
};

TreeNode::TreeNode() {
    this->value = 0;
}

TreeNode::TreeNode(int value) {
    this->value = value;
}

class Tree {
private:
    map<int, TreeNode> nodes;
    map<int, vector<int>> children;

public:
    void addNode(int value);
    void addChild(int parentValue, int childValue);
    void display(int rootValue = 0, int level = 0);
};

void Tree::addNode(int value) {
    TreeNode newnode(value);
    nodes[value] = newnode;
}

void Tree::addChild(int parentValue, int childValue) {
    children[parentValue].push_back(childValue);
    addNode(childValue);
}

void Tree::display(int rootValue, int level) {
    if (nodes.find(rootValue) == nodes.end()) return;
    cout << rootValue << endl;
    for (vector<int>::iterator iter = children[rootValue].begin(); iter != children[rootValue].end(); iter++) {
        display(*iter, level + 1);
    }
}

int main() {
    Tree tree;
    tree.addNode(1); 
    tree.addChild(1, 2);
    tree.addChild(1, 3);
    tree.addChild(2, 4);
    tree.addChild(2, 5);
    tree.addChild(3, 6);

    std::cout << "Tree Structure:\n";
    tree.display(1);  
    return 0;
}