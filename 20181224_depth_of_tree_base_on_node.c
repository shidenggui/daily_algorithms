#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
    while (i < n && inorder[i] != preorder[0]) i++;
    if (i == n)
        fatal_error("invalid input");
    root->left = build_tree(preorder + 1, inorder, i);
    root->right = build_tree(preorder + 1 + i, inorder + i + 1, n - i - 1);
    return root;
}

void free_tree(TreeNode *root) {
    if (!root)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void print_tree(TreeNode *root, int space) {
    if (!root)
        return;
    print_tree(root->right, space + 5);
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("%d\n", root->value);
    print_tree(root->left, space + 5);
}

int max(int a, int b) {
    return a >= b? a: b;
}

int depth(TreeNode *root) {
    if (!root)
        return 0;
    int left_depth = depth(root->left);
    int right_depth = depth(root->right);
    return max(left_depth, right_depth) + 1;
}

void test_depth() {
    TreeNode *tree;

    tree = build_tree((int*)&(int[]){1, 2, 4, 5, 7, 3, 6}, (int*)&(int[]){4, 2, 7, 5, 1, 3, 6}, 7);
    print_tree(tree, 0);
    printf("depth: %d\n", depth(tree));
    assert(depth(tree) == 4);

    print_tree(tree->left, 0);
    printf("depth: %d\n", depth(tree->left));
    assert(depth(tree->left) == 3);

    print_tree(tree->right, 0);
    printf("depth: %d\n", depth(tree->right));
    assert(depth(tree->right) == 2);
    free_tree(tree);
}

int main() {
    test_depth();
}
