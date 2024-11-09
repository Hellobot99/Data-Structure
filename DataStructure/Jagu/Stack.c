#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct Node {
    element data;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

void init_Stack(Stack* stack) {
    stack->top = NULL;
}

int is_Empty(Stack* stack) {
    return (!stack->top);
}

void push(Stack* stack, element data) {
    Node* new = (Node*)malloc(sizeof(Node));
    new->data = data;
    new->next = stack->top;
    stack->top = new;
}

element pop(Stack* stack) {
    element r = stack->top->data;
    Node* node = stack->top;
    stack->top = stack->top->next;
    free(node);   
    return r;
}

element peek(Stack* stack) {
    if (!is_Empty(stack)) return stack->top->data;
    printf("스택이 비었습니다.");
    return -1;
}

void freeStack(Stack* stack) {
    while (!is_Empty(stack)) {
        Node* temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
}

int main() {
    Stack stack;
    init_Stack(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("Top of stack: %d\n", peek(&stack));

    printf("Popping value: %d\n", pop(&stack));
    printf("Popping value: %d\n", pop(&stack));

    printf("Top of stack after pops: %d\n", peek(&stack));

    printf("Popping value: %d\n", pop(&stack));

    if (is_Empty(&stack)) {
        printf("Stack is empty now.\n");
    }
    else {
        printf("Top of stack: %d\n", peek(&stack));
    }

    freeStack(&stack);

    return 0;
}