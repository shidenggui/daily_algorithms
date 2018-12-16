/*
 * 好久没手写 queue 了，结果感觉有点手生。queue 在 enqueue 和 dequeue 的时候需要变动 size，但是实际移动的指针却是对应的 rear 和 front
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define Ele TreeNode*
#define MAX_SIZE (999)

void fatal_error(char *msg) {
    printf("fatal error:%s\n", msg);
    exit(1);
}

void error(char *msg) {
    printf("error:%s\n", msg);
    exit(1);
}

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *build_tree(int *preorder, int *inorder, unsigned n) {
    if (preorder == NULL || inorder == NULL || n <= 0)
        return NULL;

    TreeNode *root = malloc(sizeof(TreeNode));
    if (root == NULL)
        fatal_error("out of space");
    root->value = preorder[0];
    int i = 0;
    while (i < n && inorder[i] != root->value) i++;
    if (i == n)
        error("invalid input");
    root->left = build_tree(preorder + 1, inorder, i);
    root->right = build_tree(preorder + 1 + i, inorder + i + 1, n - i -1);
    return root;
}

void free_tree(TreeNode *root) {
    if (root == NULL)
        return;

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

typedef struct QueueRecord {
    Ele *arr;
    int capacity;
    int size;
    int front;
    int rear;
} QueueRecord, *Queue;

Queue create_queue(int size) {
    if (size < 2) {
        size = 2;
    }
    Queue q = malloc(sizeof(QueueRecord));
    if (q == NULL)
        fatal_error("out of space");

    q->arr = malloc(sizeof(Ele) * size);
    if (q->arr == NULL)
        fatal_error("out of space");

    q->capacity = size;
    q->size = 0;
    q->front = 1;
    q->rear = 0;
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

void enqueue(Ele value, Queue q) {
    if (is_full(q))
        error("queue is full, cant enqueue");

    q->size++;
    q->rear = (q->rear + 1) % q->capacity;
    q->arr[q->rear] = value;
}

Ele dequeue(Queue q) {
    if (is_empty(q))
        error("queue is empty, cant dequeue");

    q->size--;
    Ele poped = q->arr[q->front];
    q->front = (q->front + 1) % q->capacity;
    return poped;
}

void print_tree_by_level(TreeNode *root) {
    if (root == NULL)
        return;
    Queue q = create_queue(MAX_SIZE);
    enqueue(root, q);
    while (!is_empty(q)) {
        TreeNode* node = dequeue(q);
        printf("%d ", node->value);

        if (node->left)
            enqueue(node->left, q);
        if (node->right)
            enqueue(node->right, q);
    }

    free_queue(q);
}

void print_tree(TreeNode *root, int space) {
    if (root == NULL)
        return;
    print_tree(root->right, space + 5);

    for (int i = 0; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->value);
    
    print_tree(root->left, space + 5);
}

void test_print_tree_by_level() {
    TreeNode *tree;
    tree = build_tree((int*)&(int[]){8, 6, 5, 7, 10, 9, 11}, (int*)&(int[]){5, 6, 7, 8, 9, 10, 11}, 7);
    print_tree(tree, 0);
    printf("print by level:\n");
    print_tree_by_level(tree);
    printf("\n");
    free_tree(tree);

    tree = build_tree((int*)&(int[]){8, 6, 5}, (int*)&(int[]){5, 6, 8}, 3);

    print_tree(tree, 0);
    printf("print by level:\n");
    print_tree_by_level(tree);
    free_tree(tree);
}

int main() {
    test_print_tree_by_level();
}
