#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 999
#define QUEUE_MIN_SIZE 2
#define EleType TreeNode*

void fatal_error(char *msg) {
    printf("fatal error: %s", msg);
    exit(1);
}

void error(char *msg) {
    printf("error: %s", msg);
    exit(1);
}

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

void visit(TreeNode *root) {
    printf("visit %d\n", root->val);
}

typedef struct QueueStruct {
    EleType *arr;
    int capacity;
    int size;
    int front;
    int rear;
} QueueStruct, *Queue;

Queue create_queue(int size) {
    if (size < QUEUE_MIN_SIZE)
        size = QUEUE_MIN_SIZE;
    Queue q = malloc(sizeof(QueueStruct));
    if (q == NULL)
        fatal_error("out of space");
    q->arr = malloc(sizeof(EleType) * size);
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

void enqueue(EleType val, Queue q) {
    if (is_full(q))
        error("queue is full, cant enqueue");
    q->rear = (q->rear + 1) % q->capacity;
    q->arr[q->rear] = val;
    q->size++;
}

EleType dequeue(Queue q) {
    if (is_empty(q))
        error("queue is empty, cant dequeue");
    EleType val = q->arr[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return val;
}

void traverse_tree_by_level(TreeNode *root) {
    if (root == NULL)
        return;
    Queue q = create_queue(MAX_SIZE);
    enqueue(root, q);
    while (!is_empty(q)) {
        TreeNode *node = dequeue(q);
        visit(node);
        if (node->left)
            enqueue(node->left, q);
        if (node->right)
            enqueue(node->right, q);
    }
    free_queue(q);
}

void test_traverse_tree_by_level() {
    TreeNode *three_left = &(TreeNode){.left=NULL, .right=NULL, .val=4};
    TreeNode *three_right = &(TreeNode){.left=NULL, .right=NULL, .val=5};
    TreeNode *two_left = &(TreeNode){.left=NULL, .right=NULL, .val=2};
    TreeNode *two_right = &(TreeNode){.left=three_left, .right=three_right, .val=3};
    TreeNode *root = &(TreeNode){.left=two_left, .right=two_right, .val=1};
    traverse_tree_by_level(root);
}

int main() {
    test_traverse_tree_by_level();
}
