/*
 * 根据对二叉树 preorder 和 inorder 的遍历序列重建树
 * 关键点：
 * 1. preorder 的排序是第一个为 root，然后为左子树的节点，右子树的节点
 * 2. inorder 的排序是中间某个节点为 root，然后左边为左子树，右边为右子树
 * 思路：
 * 1. 编写 base cases
 * 2. 取 preorder 的第一个值作为 root 的 value，构建 root
 * 3. 根据该值遍历 inorder 找到对应的 root 值的下标 i，如果不存在则报错(这里没有考虑值重复的情况，如果有的话，则需要依次检查每个值能否正确构建对应的树)
 * 4. 这时候左子树有 i 个节点， preorder[1: i + 1] 和 inorder[0: i] 即为该 root 的左子树， preorder[i + 1: ] 和 inorder[i + 1:] 即为右子树
 * 5. 递归调用即可
*/
#include <stdlib.h>
#include <stdio.h>

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

void fatal_error(char *msg) {
    printf("fatal error: %s\n", msg);
    exit(1);
}


void error(char *msg) {
    printf("error: %s\n", msg);
    exit(1);
}

TreeNode *rebuild(int *preorder, int *inorder, int n) {
    if (n <= 0)
        return NULL;

    TreeNode *root = malloc(sizeof(TreeNode));
    if (root == NULL)
        fatal_error("out of space");
    root->value = preorder[0];

    int i = 0;
    while (i < n && inorder[i] != root->value) i++;
    if (i == n)
        error("invalid input");
    root->left = rebuild(preorder + 1, inorder, i);
    root->right = rebuild(preorder + 1 + i, inorder + i + 1, n - i - 1);
    return root;
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

void free_tree(TreeNode *root) {
    if (root == NULL)
        return;

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void test_rebuild() {
    int preorder[] = {1, 2, 4, 7, 3, 5, 6, 8};
    int inorder[] = {4, 7, 2, 1, 5, 3, 8, 6};
    TreeNode *tree = rebuild(preorder, inorder, sizeof(preorder) / sizeof(int));
    print_tree(tree, 0);
    free_tree(tree);
}

int main() {
    test_rebuild();
}
