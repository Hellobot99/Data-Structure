#include <iostream>
#include <vector>
#include <map>

using namespace std;

class LinkedList {
public:

    void insert(int value);            // 리스트에 값 추가
    void remove(int index);            // 인덱스로 노드 삭제
    int get(int index);          // 인덱스로 값 조회
    int size();                  // 리스트 크기 반환
    bool isEmpty();              // 리스트가 비어 있는지 확인
    void display();              // 리스트의 모든 값을 출력

private:
    vector<int> values;           // 노드 값을 저장하는 벡터
    map<int, int> indexMap;       // 인덱스와 값을 매핑하기 위한 맵
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
    list.display(); // 출력: List contents: 10 20 30 

    std::cout << "Value at index 1: " << list.get(1) << std::endl; // 출력: Value at index 1: 20
    std::cout << "Is the list empty? " << (list.isEmpty() ? "Yes" : "No") << std::endl; // 출력: No
    std::cout << "Size of the list: " << list.size() << std::endl; // 출력: Size of the list: 3

    return 0;
}