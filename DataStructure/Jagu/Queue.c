#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct Node {
    element data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

element is_Empty(Queue* queue) {
    return(!queue->front);
}

void enqueue(Queue* queue, element value) {
    Node* new = (Node*)malloc(sizeof(Node));
    new->data = value;
    if (is_Empty(queue)) {
        queue->front = new;
        queue->rear = new;
        new->next = new;
    }
    else {
        queue->rear->next = new;
        queue->rear = new;
        new->next = queue->front;
    }   
}

element dequeue(Queue* queue) {
    if (is_Empty(queue)) {
        printf("큐가 비었습니다.");
        return -1;
    }

    element r = queue->front->data;
    Node* temp = queue->front;

    if (queue->front == queue->rear) {
        queue->front = queue->rear = NULL;
    }
    else {
        queue->front = queue->front->next;
        queue->rear->next = queue->front;
    }
    
    free(temp);

    return r;
}

element peek(Queue* queue) {
    if(!is_Empty(queue))return queue->front->data;
    return -1;
}

void freeQueue(Queue* queue) {
    if (is_Empty(queue)) return;

    Node* current = queue->front;
    Node* temp;

    while (current != queue->rear) {
        temp = current;
        current = current->next;
        free(temp);
    }

    free(current);
    free(queue);
}

int main() {
    Queue* q = createQueue();

    printf("큐에 10, 20, 30을 추가합니다.\n");
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);

    printf("큐의 첫 번째 값: %d\n", peek(q));

    printf("큐에서 제거한 값: %d\n", dequeue(q));
    printf("큐에서 제거한 값: %d\n", dequeue(q));
    printf("큐에서 제거한 값: %d\n", dequeue(q));

    printf("큐가 비었는지 확인: %s\n", is_Empty(q) ? "비어있음" : "비어있지 않음");

    printf("큐에 40, 50을 추가합니다.\n");
    enqueue(q, 40);
    enqueue(q, 50);
    printf("큐의 첫 번째 값: %d\n", peek(q));

    printf("큐에서 제거한 값: %d\n", dequeue(q));
    printf("큐에서 제거한 값: %d\n", dequeue(q));

    printf("큐가 비었는지 확인: %s\n", is_Empty(q) ? "비어있음" : "비어있지 않음");

    freeQueue(q);
    return 0;
}