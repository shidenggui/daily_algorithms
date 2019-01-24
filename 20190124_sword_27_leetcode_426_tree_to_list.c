/*
 * 思路：
 * 使用递归。递归函数的含义是将该 bst 转换为 sorted double linked list，然后通过 tail 参数返回最后一个节点的值。
 * 而我们在递归中，先递归转换左子树，如果左子树的 tail 存在，则将 root->left 指向 *tail，(*tail)->right = root，然后将 *tail = root,
 * 然后递归转换右子树。递归过程结束后，外面的函数的 root 就变成了中间的节点，依次从后向前遍历到头结点，然后返回
 */
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


void tree_to_list_core(TreeNode *root, TreeNode **tail) {
    if (!root)
        return;

    tree_to_list_core(root->left, tail);
    if (*tail) {
        (*tail)->right = root;
        root->left = *tail;
    }
    *tail = root;
    tree_to_list_core(root->right, tail);
}

TreeNode *tree_to_list(TreeNode *root) {
    if (!root)
        return NULL;

    TreeNode *tail = NULL;
    tree_to_list_core(root, &tail);
    while (root->left)
        root = root->left;
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
