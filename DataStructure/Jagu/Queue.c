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
        printf("ť�� ������ϴ�.");
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

    printf("ť�� 10, 20, 30�� �߰��մϴ�.\n");
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);

    printf("ť�� ù ��° ��: %d\n", peek(q));

    printf("ť���� ������ ��: %d\n", dequeue(q));
    printf("ť���� ������ ��: %d\n", dequeue(q));
    printf("ť���� ������ ��: %d\n", dequeue(q));

    printf("ť�� ������� Ȯ��: %s\n", is_Empty(q) ? "�������" : "������� ����");

    printf("ť�� 40, 50�� �߰��մϴ�.\n");
    enqueue(q, 40);
    enqueue(q, 50);
    printf("ť�� ù ��° ��: %d\n", peek(q));

    printf("ť���� ������ ��: %d\n", dequeue(q));
    printf("ť���� ������ ��: %d\n", dequeue(q));

    printf("ť�� ������� Ȯ��: %s\n", is_Empty(q) ? "�������" : "������� ����");

    freeQueue(q);
    return 0;
}