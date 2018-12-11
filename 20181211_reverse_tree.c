#include <stdio.h>

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

void reverse(TreeNode *root) {
    if (root == NULL) 
        return;
    reverse(root->left);
    reverse(root->right);
    TreeNode *tmp = root->left;
    root->left = root->right;
    root->right = tmp;
}

void print_tree(TreeNode *root, int space) {
    if (root == NULL)
        return;
    print_tree(root->right, space + 5);

    for (int i = 0; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->value);

    print_tree(root->left, space + 5);
}

void test_reverse() {
    TreeNode *left_left = &(TreeNode){.value=21, .left=NULL, .right=NULL};
    TreeNode *left = &(TreeNode){.value=2, .left=left_left, .right=NULL};
    TreeNode *right = &(TreeNode){.value=3, .left=NULL, .right=NULL};
    printf("Left sub tree:\n");
    print_tree(left, 5);
    printf("after reverse:\n");
    reverse(left);
    print_tree(left, 5);

    TreeNode *root = &(TreeNode){.value=1, .left=left, .right=right};
    printf("Total tree:\n");
    print_tree(root, 5);
    printf("after reverse:\n");
    reverse(root);
    print_tree(root, 5);
}

int main() {
    test_reverse();
}
