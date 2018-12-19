#include <stdlib.h>
#include <stdio.h>

void fatal_error(char *msg) {
    printf("fatal error: %s\n", msg);
    exit(1);
}

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

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
        fatal_error("invalid input");
    root->left = build_tree(preorder + 1, inorder, i);
    root->right = build_tree(preorder + 1 + i, inorder + i + 1, n - i - 1);
    return root;
}

void print_list(TreeNode *root) {
    if (root == NULL)
        return;
    TreeNode *prev = NULL;

    printf("in order:\n");
    while (root) {
        printf("%d->", root->value);
        prev = root;
        root = root->right;
    }
    printf("N\n");
    printf("reverse order:\n");
    while (prev) {
        printf("%d->", prev->value);
        prev = prev->left;
    }
    printf("N\n");
}

void free_list(TreeNode *root) {
    while (root) {
        TreeNode *tmp = root;
        root = root->right;
        free(root);
    }
}

void print_tree(TreeNode *root, int space) {
    if (root == NULL)
        return;
    print_tree(root->right, space + 5);
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("%d\n", root->value);
    print_tree(root->left, space + 5);
}

void tree2list(TreeNode *root, TreeNode **last) {
    if (root == NULL)
        return;

    tree2list(root->left, last);
    if (*last) {
        (*last)->right = root;
        root->left = *last;
    }
    *last = root;
    tree2list(root->right, last);
}

TreeNode *tree_to_list(TreeNode *root) {
    if (root == NULL)
        return NULL;

    TreeNode *last = NULL;
    tree2list(root, &last);
    while (root->left) root = root->left;
    return root;
}

void test_tree_to_list() {
    TreeNode *tree;
    tree = build_tree((int*)&(int[]){10, 6, 4, 8, 14, 12, 16}, (int*)&(int[]){4, 6, 8, 10, 12, 14, 16}, 7);
    print_tree(tree, 0);
    tree = tree_to_list(tree);
    print_list(tree);
    free_list(tree);

    printf("\nnew tree:\n");
    tree = build_tree((int*)&(int[]){10}, (int*)&(int[]){10}, 1);
    print_tree(tree, 0);
    tree = tree_to_list(tree);
    print_list(tree);
    free_list(tree);

    printf("\nnew tree:\n");
    tree = build_tree((int*)&(int[]){10, 7}, (int*)&(int[]){7, 10}, 2);
    print_tree(tree, 0);
    tree = tree_to_list(tree);
    print_list(tree);
    free_list(tree);

    printf("\nnew tree:\n");
    tree = build_tree((int*)&(int[]){10, 7, 15}, (int*)&(int[]){7, 10, 15}, 3);
    print_tree(tree, 0);
    tree = tree_to_list(tree);
    print_list(tree);
    free_list(tree);
}

int main() {
    test_tree_to_list();
}
