#include <stdio.h>
#include <stdlib.h>

#define MAX 100
struct Stack {
    int arr[MAX];
    int top;
};
void initStack(struct Stack* s) {
    s->top = -1;
}
int isEmpty(struct Stack* s) {
    return s->top == -1;
}
int isFull(struct Stack* s) {
    return s->top == MAX - 1;
}

void push(struct Stack* s, int x) {
    if (isFull(s)) {
        printf("Stack overflow!\n");
        return;
    }
    s->arr[++(s->top)] = x;
}

int pop(struct Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow!\n");
        return -1;
    }
    return s->arr[(s->top)--];
}

int peek(struct Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return s->arr[s->top];
}

struct Queue {
    struct Stack s1, s2;
};

void initQueue(struct Queue* q) {
    initStack(&(q->s1));
    initStack(&(q->s2));
}

void enqueue(struct Queue* q, int x) {

    while (!isEmpty(&(q->s1))) {
        push(&(q->s2), pop(&(q->s1)));
    }

    push(&(q->s1), x);
    while (!isEmpty(&(q->s2))) {
        push(&(q->s1), pop(&(q->s2)));
    }

    printf("Enqueued %d\n", x);
}

void dequeue(struct Queue* q) {
    if (isEmpty(&(q->s1))) {
        printf("Queue is empty!\n");
        return;
    }
    int x = pop(&(q->s1));
    printf("Dequeued %d\n", x);
}
void display(struct Queue* q) {
    if (isEmpty(&(q->s1))) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = 0; i <= q->s1.top; i++) {
        printf("%d ", q->s1.arr[i]);
    }
    printf("\n");
}

int main() {
    struct Queue q;
    initQueue(&q);

    int choice, value;

    while (1) {
        printf("\n--- Queue Using Two Stacks (Costly Push) ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            enqueue(&q, value);
            break;
        case 2:
            dequeue(&q);
            break;
        case 3:
            display(&q);
            break;
        case 4:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
