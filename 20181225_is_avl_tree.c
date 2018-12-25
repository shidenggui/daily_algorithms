#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

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
    if (!root)
        fatal_error("out of space");
    root->value = preorder[0];
    int i = 0;
    while (i < n && inorder[i] != preorder[0]) i++;
    if (i == n)
        fatal_error("input invalid");
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

bool is_avl_tree_core(TreeNode *root, int *depth) {
    if (!root) {
        *depth = 0;
        return true;
    }
    int left, right;
    if (!is_avl_tree_core(root->left, &left) || !is_avl_tree_core(root->right, &right))
        return false;
    int diff = left - right;
    if (diff < -1 || diff > 1)
        return false;
    *depth = 1 + (left > right? left: right);
    return true;
}

bool is_avl_tree(TreeNode *root) {
    int depth = 0;
    return is_avl_tree_core(root, &depth);
}

void test_is_avl_tree() {
    assert(is_avl_tree(NULL) == true);

    TreeNode *tree;
    tree = build_tree((int*)&(int[]){1, 2, 4, 5, 7, 3, 6}, (int*)&(int[]){4, 2, 7, 5, 1, 3, 6}, 7);
    printf("tree:\n");
    print_tree(tree, 0);
    assert(is_avl_tree(tree) == true);
    free_tree(tree);

    tree = build_tree((int*)&(int[]){1, 2, 5, 7}, (int*)&(int[]){2, 7, 5, 1}, 4);
    printf("tree:\n");
    print_tree(tree, 0);
    assert(is_avl_tree(tree) == false);
    free_tree(tree);
}

int main() {
    test_is_avl_tree();
}
