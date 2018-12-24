/*
 * 判断二叉树是否是二叉平衡树。
 * 思路：
 * 1. 最简单的是使用 depth 函数，递归不断判断左右子树的深度，但是这样的话会重复遍历二叉树。
 * 2. 利用后序遍历的性质，先遍历左子树，在遍历右子树，然后是根节点。如果我们依次统计左子树的深度、右子树的深度，然后在根节点我们就可以判断该树的左右子树是否平衡，
 * 然后在计算 root 节点的深度返回即可
 */
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
    if (root == NULL)
        fatal_error("out of space");
    root->value = preorder[0];
    int i = 0;
    while (i < n && inorder[i] != preorder[0]) i++;
    if (i == n)
        fatal_error("invalid input");
    root->left = build_tree(preorder + 1, inorder, i);
    root->right = build_tree(preorder + 1 + i, inorder + i + 1, n - i -1);
    return root;
}

void free_tree(TreeNode *tree) {
    if (!tree)
        return;
    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
}

void print_tree(TreeNode *tree, int space) {
    if (!tree)
        return;
    print_tree(tree->right, space + 5);
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("%d\n", tree->value);
    print_tree(tree->left, space + 5);
}

bool is_avl_tree_core(TreeNode *root, int *depth) {
    if (!root) {
        *depth = 0;
        return true;
    }

    int left, right;
    // 如果左右子树不是 avl_tree 直接返回 false
    if (!is_avl_tree_core(root->left, &left) || !is_avl_tree_core(root->right, &right))
        return false;

    // 比较 root 是否符合 avl_tree 的条件
    int diff = left - right;
    if (diff < -1 || diff > 1)
        return false;
    // 更新 root 的深度, 这里忘记加括号的话会导致 1 + left 成为条件，导致 *depth 永远为 0
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
