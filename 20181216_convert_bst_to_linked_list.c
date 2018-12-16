#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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

void print_tree(TreeNode *root, int space) {
    if (root == NULL)
        return;
    print_tree(root->right, space + 5);

    for (int i = 0; i < space; i++) {
        printf(" ") ;
    }
    printf("%d\n", root->value);
    print_tree(root->left, space + 5);
}

TreeNode* build_tree(int *preorder, int *inorder, int n) {
    if (preorder == NULL || inorder == NULL || n <= 0)
        return NULL;
    TreeNode* root = malloc(sizeof(TreeNode));
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
    if (!root)
        return;

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
void print_list(TreeNode *root) {
    if (root == NULL) {
        printf("N\n");
        return;
    }
    while (root) {
        printf("%d->", root->value);
        root = root->right;
    }

    printf("N\n");
}


TreeNode *convert_bst4list(TreeNode *root, bool is_left) {
    if (root == NULL)
        return NULL;

    TreeNode *left = convert_bst4list(root->left, true);
    if (left != NULL) {
        left->right = root;
        root->left = left;
    }

    TreeNode *right = convert_bst4list(root->right, false);
    if (right != NULL) {
        right->left = root;
        root->right = right;
    }

    if (is_left)
        return right? right: root;
    return left? left: root;
}

TreeNode *convert(TreeNode *root) {
    root = convert_bst4list(root, false);
    while (root->left != NULL)
        root = root->left;
    return root;
}

void test_convert_bst4list() {
    TreeNode *tree;
    tree = build_tree((int*)&(int[]){10, 6, 4, 8, 14, 12, 16}, (int*)&(int[]){4, 6, 8, 10, 12, 14, 16}, 7);
    print_tree(tree, 0);
    TreeNode *start = convert(tree);
    printf("after convert to list:\n");
    print_list(start);
    free_tree(tree);
}

int main() {
    test_convert_bst4list();
}
