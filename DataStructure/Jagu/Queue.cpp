#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Queue {
public:
    void enqueue(int value);      // ť�� �� �߰�
    void dequeue();               // ť���� �� ����
    int front();                  // ť�� ���� �� �� ��ȸ
    bool isEmpty();               // ť�� ��� �ִ��� Ȯ��
    int size();                   // ť ũ�� ��ȯ

private:
    vector<int> values;           // ť ���� �����ϴ� ����
    map<int, int> indexMap;       // �ε����� ���� �����ϱ� ���� ��
};

void Queue::enqueue(int value) {
    values.push_back(value);
    indexMap[values.size() - 1] = value;
}

void Queue::dequeue() {
    values.erase(values.begin());
    indexMap.erase(0);
    for (int i = 0; i < indexMap.size() - 1; i++) {
        indexMap[i] = indexMap[i + 1];
    }
}