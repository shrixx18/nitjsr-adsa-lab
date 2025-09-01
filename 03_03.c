#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Queue structure
struct Queue {
    int arr[MAX];
    int front, rear, size;
};

// Initialize queue
void initQueue(struct Queue* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

// Check if queue is empty
int isEmpty(struct Queue* q) {
    return q->size == 0;
}

// Check if queue is full
int isFull(struct Queue* q) {
    return q->size == MAX;
}

// Enqueue
void enqueue(struct Queue* q, int x) {
    if (isFull(q)) {
        printf("Queue overflow!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX;
    q->arr[q->rear] = x;
    q->size++;
}

// Dequeue
int dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Queue underflow!\n");
        return -1;
    }
    int val = q->arr[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return val;
}

// Peek
int front(struct Queue* q) {
    if (isEmpty(q)) {
        return -1;
    }
    return q->arr[q->front];
}

// ===============================
// Stack using 2 Queues - Method 1
// ===============================
struct Stack1 {
    struct Queue q1, q2;
};

void initStack1(struct Stack1* s) {
    initQueue(&(s->q1));
    initQueue(&(s->q2));
}

// Push (Enqueue costly)
void push1(struct Stack1* s, int x) {
    // Step 1: Enqueue into q2
    enqueue(&(s->q2), x);

    // Step 2: Move all elements from q1 to q2
    while (!isEmpty(&(s->q1))) {
        enqueue(&(s->q2), dequeue(&(s->q1)));
    }

    // Step 3: Swap q1 and q2
    struct Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;

    printf("Pushed %d (Method 1)\n", x);
}

// Pop (efficient)
void pop1(struct Stack1* s) {
    if (isEmpty(&(s->q1))) {
        printf("Stack is empty!\n");
        return;
    }
    int x = dequeue(&(s->q1));
    printf("Popped %d (Method 1)\n", x);
}

// ===============================
// Stack using 2 Queues - Method 2
// ===============================
struct Stack2 {
    struct Queue q1, q2;
};

void initStack2(struct Stack2* s) {
    initQueue(&(s->q1));
    initQueue(&(s->q2));
}

// Push (efficient)
void push2(struct Stack2* s, int x) {
    enqueue(&(s->q1), x);
    printf("Pushed %d (Method 2)\n", x);
}

// Pop (Dequeue costly)
void pop2(struct Stack2* s) {
    if (isEmpty(&(s->q1))) {
        printf("Stack is empty!\n");
        return;
    }

    // Move elements except last to q2
    while (s->q1.size > 1) {
        enqueue(&(s->q2), dequeue(&(s->q1)));
    }

    // Pop the last element (stack top)
    int x = dequeue(&(s->q1));
    printf("Popped %d (Method 2)\n", x);

    // Swap q1 and q2
    struct Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;
}

// ===============================
// Demo
// ===============================
int main() {
    struct Stack1 s1;
    struct Stack2 s2;

    initStack1(&s1);
    initStack2(&s2);

    // Method 1 demo
    push1(&s1, 10);
    push1(&s1, 20);
    push1(&s1, 30);
    pop1(&s1);
    pop1(&s1);

    // Method 2 demo
    push2(&s2, 100);
    push2(&s2, 200);
    push2(&s2, 300);
    pop2(&s2);
    pop2(&s2);

    return 0;
}
