/*
 * 输入一个二叉排序树，将其转换为对应的双向排序链表。
 * 思路：
 * 1. 这里利用了对二叉搜索树进行中序遍历时，遍历的结果即为排序的结果
 * 2. 使用递归先转换左子树，然后使用一个额外的指向 TreeNode * 的 last 指针来保存左子树的最右侧的节点（也即左子树中最大的节点），然后判断如果该 last 指向的节点存在的话，则将 root 节点链接在 (*last) 上，然后转换右子树。
 * 3. 最后将拿到的根节点往前回溯，拿到转为链表后的头结点即可。
 * 容易犯错的地方：
 * 1. 我最开始判断是否链接 (*last) 和 root 是根据 root->left，但其实不是的，因为右子树的最小值的 作为 root 时，left 肯定指向 NULL，而此时我们需要做的是将最小值链接到它的根节点（也即之前它的父亲的左子树，他的父亲转换好的排序链表的末尾)，所以应该判断 (*last) 是否为 NULL
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
        fatal_error("input valid");
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
    print_tree(root->right, space + 5);
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("%d\n", root->value);
    print_tree(root->left, space + 5);
}

void print_list(TreeNode *root) {
    printf("in order:\n");
    TreeNode *prev = NULL;
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
        free(tmp);
    }
}

void tree2list(TreeNode *root, TreeNode **last) {
    if (root == NULL)
        return;

    tree2list(root->left, last);
    if (*last) {
        root->left = *last;
        (*last)->right = root;
    }

    *last = root;
    tree2list(root->right, last);

}
TreeNode *tree_to_list(TreeNode *root) {
    if (root == NULL)
        return NULL;
    TreeNode *last_ptr = NULL;
    tree2list(root, &last_ptr);
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
