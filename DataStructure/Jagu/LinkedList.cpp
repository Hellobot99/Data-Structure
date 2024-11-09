#include <iostream>
#include <vector>
#include <map>

using namespace std;

class LinkedList {
public:

    void insert(int value);            // ����Ʈ�� �� �߰�
    void remove(int index);            // �ε����� ��� ����
    int get(int index);          // �ε����� �� ��ȸ
    int size();                  // ����Ʈ ũ�� ��ȯ
    bool isEmpty();              // ����Ʈ�� ��� �ִ��� Ȯ��
    void display();              // ����Ʈ�� ��� ���� ���

private:
    vector<int> values;           // ��� ���� �����ϴ� ����
    map<int, int> indexMap;       // �ε����� ���� �����ϱ� ���� ��
};

void LinkedList::insert(int value) {
    values.push_back(value);
    indexMap[values.size() - 1] = value;
}

void LinkedList::remove(int index) {
    if (index != 0, index < values.size()) {
        values.erase(values.begin() + index);
        indexMap.erase(index);
        for (int i = index; i < values.size(); ++i) {
            indexMap[i] = values[i];
        }
    }
}

int LinkedList::get(int index) {
    return values[index];
}

int LinkedList::size() {
    return values.size();
}

bool LinkedList::isEmpty() {
    return values.empty();
}

void LinkedList::display() {
    for (int i = 0; i < indexMap.size(); i++) {
        cout << indexMap[i] << " ";
    }
    cout << endl;
}

int main() {
    LinkedList list;
    list.insert(10);
    list.insert(20);
    list.insert(30);

    std::cout << "List contents: ";
    list.display(); // ���: List contents: 10 20 30 

    std::cout << "Value at index 1: " << list.get(1) << std::endl; // ���: Value at index 1: 20
    std::cout << "Is the list empty? " << (list.isEmpty() ? "Yes" : "No") << std::endl; // ���: No
    std::cout << "Size of the list: " << list.size() << std::endl; // ���: Size of the list: 3

    return 0;
}