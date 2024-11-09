#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Stack {
public:
    void push(int value);    // ���ÿ� �� �߰�
    void pop();              // ���ÿ��� �� ����
    int top();               // ������ ���� �� �� ��ȸ
    bool isEmpty();          // ������ ��� �ִ��� Ȯ��
    int size();              // ���� ũ�� ��ȯ

private:
    std::vector<int> values; // ���� ���� �����ϴ� ����
    std::map<int, int> indexMap; // �ε����� ���� �����ϱ� ���� ��
};

void Stack::push(int value) {
    values.push_back(value);
    indexMap[values.size()-1] = value;
}

void Stack::pop() {
    values.erase(values.begin() + values.size() - 1);
    indexMap.erase(values.size() - 1);
}

int Stack::top() {
    return values[values.size() - 1];
}

bool Stack::isEmpty() {
    return !values.size();
}

int Stack::size() {
    return values.size();
}

int main() {
    Stack stack;

    // ���ÿ� �� �߰�
    cout << "���ÿ� 10, 20, 30 �߰�" << endl;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    // ���� ���� ũ�� ���
    cout << "���� ���� ũ��: " << stack.size() << endl;

    // ������ ���� �� �� ��ȸ
    cout << "������ ���� �� ��: " << stack.top() << endl;

    // ���ÿ��� �� ����
    cout << "���ÿ��� �� ����" << endl;
    stack.pop();
    cout << "���� ���� ũ��: " << stack.size() << endl;

    // ������ ���� �� �� ��ȸ
    cout << "������ ���� �� ��: " << stack.top() << endl;

    // ��� �� ����
    cout << "��� �� ����" << endl;
    stack.pop();
    stack.pop();

    // ������ ��� �ִ��� Ȯ��
    if (stack.isEmpty()) {
        cout << "������ ��� �ֽ��ϴ�." << endl;
    }

    // ������ ũ��
    cout << "���� ũ��: " << stack.size() << endl;

    return 0;
}
