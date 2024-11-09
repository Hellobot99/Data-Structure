#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Stack {
public:
    void push(int value);    // 스택에 값 추가
    void pop();              // 스택에서 값 제거
    int top();               // 스택의 가장 위 값 조회
    bool isEmpty();          // 스택이 비어 있는지 확인
    int size();              // 스택 크기 반환

private:
    std::vector<int> values; // 스택 값을 저장하는 벡터
    std::map<int, int> indexMap; // 인덱스와 값을 매핑하기 위한 맵
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

    // 스택에 값 추가
    cout << "스택에 10, 20, 30 추가" << endl;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    // 현재 스택 크기 출력
    cout << "현재 스택 크기: " << stack.size() << endl;

    // 스택의 가장 위 값 조회
    cout << "스택의 가장 위 값: " << stack.top() << endl;

    // 스택에서 값 제거
    cout << "스택에서 값 제거" << endl;
    stack.pop();
    cout << "현재 스택 크기: " << stack.size() << endl;

    // 스택의 가장 위 값 조회
    cout << "스택의 가장 위 값: " << stack.top() << endl;

    // 모든 값 제거
    cout << "모든 값 제거" << endl;
    stack.pop();
    stack.pop();

    // 스택이 비어 있는지 확인
    if (stack.isEmpty()) {
        cout << "스택이 비어 있습니다." << endl;
    }

    // 스택의 크기
    cout << "스택 크기: " << stack.size() << endl;

    return 0;
}
