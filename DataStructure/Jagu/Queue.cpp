#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Queue {
public:
    void enqueue(int value);      // 큐에 값 추가
    void dequeue();               // 큐에서 값 제거
    int front();                  // 큐의 가장 앞 값 조회
    bool isEmpty();               // 큐가 비어 있는지 확인
    int size();                   // 큐 크기 반환

private:
    vector<int> values;           // 큐 값을 저장하는 벡터
    map<int, int> indexMap;       // 인덱스와 값을 매핑하기 위한 맵
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