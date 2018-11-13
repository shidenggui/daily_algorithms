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

typedef struct QueueStruct {
    int *arr;
    int capacity;
    int size;
    int front;
    int rear;
} QueueStruct, *Queue;

Queue create_queue(int size) {
    if (size < 2)
        size = 2;
    Queue q = malloc(sizeof(QueueStruct));
    if (q == NULL)
        fatal_error("out of space");

    q->arr = malloc(sizeof(int) * size);
    if (q->arr == NULL)
        fatal_error("out of space");

    q->capacity = size;
    q->size = 0;
    q->rear = 0;
    q->front = 1;
    return q;
}

void free_queue(Queue q) {
    if (q == NULL)
        return;
    free(q->arr);
    free(q);
}

bool is_empty(Queue q) {
    return q->size == 0;
}

bool is_full(Queue q) {
    return q->size == q->capacity;
}

void enqueue(int value, Queue q) {
    if (is_full(q))
        error("queue is full, cant enqueue");
    q->size++;
    q->rear = (++q->rear) % q->capacity;
    q->arr[q->rear] = value;
}

int dequeue(Queue q) {
    if (is_empty(q))
        error("queue is empty, cant dequeue");
    q->size--;
    int top = q->arr[q->front];
    q->front = (++q->front) % q->capacity;
    return top;
}

int qsize(Queue q) {
    return q->size;
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
    assert(is_full(q));
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
