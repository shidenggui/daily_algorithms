#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

void fatal_error(char *msg) {
    printf("fatal error: %s\n", msg);
    exit(1);
}

void error(char *msg) {
    printf("fatal error: %s\n", msg);
    exit(1);
}

typedef struct Node {
    int val; // compatible for leetcode
    struct Node *next;
} Node;

typedef struct QueueStruct {
    Node *front;
    Node *rear;
} QueueStruct, *Queue;

// arg size just for compatible for array implementation
Queue create_queue(int size) {
    Queue q = malloc(sizeof(QueueStruct));
    if (q == NULL)
        fatal_error("out of space");
    q->front = q->rear = NULL;
    return q;
}

void free_queue(Queue q) {
    if (q == NULL)
        return;
    while (q->front) {
        Node *tmp = q->front;
        q->front = q->front->next;
        free(tmp);
    }
    free(q);
}

bool is_empty(Queue q) {
    return q->front == NULL;
}

bool is_full(Queue q) {
    return false;
}

void enqueue(int val, Queue q) {
    Node *inserted = malloc(sizeof(Node));
    if (inserted == NULL)
        fatal_error("out of space");
    inserted->val = val;
    inserted->next = NULL;
    if (is_empty(q)) {
        q->front = q->rear = inserted;
        return;
    }

    q->rear->next = inserted;
    q->rear = inserted;
}

int dequeue(Queue q) {
    if (is_empty(q))
        error("queue is empty, cant dequeue");
    Node *poped = q->front;
    int val = poped->val;

    q->front = poped->next;
    if (q->front == NULL) 
        q->rear = NULL;
    free(poped);
    return val;
}

int qsize(Queue q) {
    int size = 0;
    Node *node = q->front;
    while (node) {
        size++;
        node = node->next;
    }
    return size;
}

void test_queue() {
    Queue q = create_queue(3);
    assert(is_empty(q));
    assert(!is_full(q));
    assert(qsize(q) == 0);

    enqueue(1, q);
    assert(!is_empty(q));
    assert(!is_full(q));
    assert(qsize(q) == 1);

    int value = dequeue(q);
    assert(is_empty(q));
    assert(!is_full(q));
    assert(qsize(q) == 0);
    assert(value == 1);

    enqueue(1, q);
    enqueue(2, q);
    enqueue(3, q);
    assert(!is_empty(q));
    assert(!is_full(q));
    assert(qsize(q) == 3);

    assert(dequeue(q) == 1);
    assert(dequeue(q) == 2);
    assert(dequeue(q) == 3);
    assert(is_empty(q));
    assert(qsize(q) == 0);
}

int main() {
    test_queue();
}
