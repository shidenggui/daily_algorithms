#include <stdlib.h>
#include <stdio.h>

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

void mirror(TreeNode *root) {
    if (root == NULL)
        return;

    mirror(root->left);
    mirror(root->right);

    TreeNode *tmp = root->left;
    root->left = root->right;
    root->right = tmp;
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

TreeNode *build_tree(int *preorder, int *inorder, int n) {
    if (preorder == NULL || inorder == NULL)
        return NULL;
    if (n <= 0)
        return NULL;

    TreeNode *root = malloc(sizeof(TreeNode));
    if (!root)
        fatal_error("out of space");
    root->value = preorder[0];

    int i = 0;
    while (i < n && inorder[i] != root->value) i++;
    if (i == n)
        error("invalid input");

    root->left = build_tree(preorder + 1, inorder, i);
    root->right = build_tree(preorder + 1 + i, inorder + 1 + i, n - i - 1);
    return root;
}

void free_tree(TreeNode *root) {
    if (!root)
        return;

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void test_mirror() {
    TreeNode *tree;
    tree = build_tree((int*)(int[]){8, 6, 5, 7, 10, 9, 11}, (int*)(int[]){5, 6, 7, 8, 9, 10, 11}, 7);
    print_tree(tree, 0);
    printf("mirror:\n");
    mirror(tree);
    print_tree(tree, 0);
    free_tree(tree);
}

int main() {
    test_mirror();
}

