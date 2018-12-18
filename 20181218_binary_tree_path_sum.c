/*
 * 在树找到和等于指定值的路径。
 * 思路：
 * 在前序遍历的过程中用栈保存经过的路径，如果栈的和等于指定值，则打印出对应的路径即可。
 * 关键在于，递归的最后要从栈中弹出 root 节点的值。
 */
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE (999)
#define ETOS (-1)

void fatal_error(char *msg) {
    printf("fatal error: %s\n", msg);
    exit(1);
}

void error(char *msg) {
    printf("error: %s\n", msg);
    exit(1);
}

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct StackRecord {
    int *arr;
    int capacity;
    int top;
} StackRecord, *Stack;

Stack create_stack(int size) {
    Stack s = malloc(sizeof(StackRecord));
    if (s == NULL)
        fatal_error("out of space");
    s->arr = malloc(sizeof(int) * size);
    s->capacity = size;
    s->top = ETOS;
    return s;
}

void free_stack(Stack s) {
    if (s == NULL)
        return;
    free(s->arr);
    free(s);
}

bool is_empty(Stack s) {
    return s->top == ETOS;
}

bool is_full(Stack s) {
    return s->top == s->capacity - 1;
}

void push(int value, Stack s) {
    if (is_full(s))
        error("stack is full, cant push");
    s->top++;
    s->arr[s->top] = value;
}

void pop(Stack s) {
    if (is_empty(s))
        error("stack is empty, cant pop");
    s->top--;
}

int sum(Stack s) {
    int result = 0;
    for (int i = 0; i <= s->top; i++)
        result += s->arr[i];
    return result;
}

void print_path(Stack s) {
    for (int i = 0; i <= s->top; i++)
        printf("%d->", s->arr[i]);
    printf("\n");
}

void path_sum(TreeNode *root, Stack s, int k) {
    if (root == NULL)
        return;

    push(root->value, s);
    if (sum(s) == k) {
        print_path(s);
    }

    path_sum(root->left, s, k);
    path_sum(root->right, s, k);
    pop(s);
}

void binary_tree_path_sum(TreeNode *root, int k) {
    Stack s = create_stack(MAX_SIZE);
    path_sum(root, s, k);
    free_stack(s);
}

TreeNode *build_tree(int *preorder, int *inorder, int n) {
    if (!preorder || !inorder || n <= 0)
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
    root->right = build_tree(preorder + 1 + i, inorder + i + 1, n - i - 1);
    return root;
}

void free_tree(TreeNode *root) {
    if (root == NULL)
        return;

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void print_tree(TreeNode *root, int space) {
    if (root == NULL)
        return;
    print_tree(root->left, space + 5);
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("%d\n", root->value);
    print_tree(root->right, space + 5);
}

void test_binary_tree_path_sum() {
    TreeNode *tree = build_tree((int*)&(int[]){10, 5, 4, 7, 12}, (int*)&(int[]){4, 5, 7, 10, 12}, 5);
    print_tree(tree, 0);
    printf("sum 19:\n");
    binary_tree_path_sum(tree, 19);
    printf("sum 22:\n");
    binary_tree_path_sum(tree, 22);
    free_tree(tree);
}

int main() {
    test_binary_tree_path_sum();
}
