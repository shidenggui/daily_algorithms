#include <stdlib.h>
#include <stdio.h>

void fatal_error(char *msg) {
    printf("fatal error:%s\n", msg);
    exit(1);
}

typedef struct AvlNode {
    int value;
    struct AvlNode *left;
    struct AvlNode *right;
    int height;
} AvlNode, SearchNode;

int max(int a, int b) {
    return a > b? a: b;
}

int height(SearchNode *root) {
    if (root == NULL)
        return -1;
    return root->height;
}

int root_height(SearchNode *root) {
    return max(height(root->left), height(root->right)) + 1;
}

SearchNode *single_rotate_with_left(SearchNode *k2) {
    SearchNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = root_height(k2);
    k1->height = root_height(k1);
    return k1;
}

SearchNode *single_rotate_with_right(SearchNode *k1) {
    SearchNode *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = root_height(k1);
    k2->height = root_height(k2);
    return k2;
}

SearchNode *double_rotate_with_left(SearchNode *k3) {
    k3->left = single_rotate_with_right(k3->left);
    return single_rotate_with_left(k3);
}

SearchNode *double_rotate_with_right(SearchNode *k1) {
    k1->right = single_rotate_with_left(k1->right);
    return single_rotate_with_right(k1);
}

SearchNode *insert(int value, SearchNode *root) {
    if (root == NULL) {
        root = malloc(sizeof(SearchNode));
        if (root == NULL)
            fatal_error("out of space");
        root->value = value;
        root->left = root->right = NULL;
        root->height = 0;
        return root;
    }

    if (value < root->value) {
        root->left = insert(value, root->left);
        if (height(root->left) - height(root->right) == 2) {
            if (value < root->left->value)
                root = single_rotate_with_left(root);
            else
                root = double_rotate_with_left(root);
        }
    } else if (value > root->value) {
        root->right = insert(value, root->right);
        if (height(root->right) - height(root->left) == 2) {
            if (value > root->right->value)
                root = single_rotate_with_right(root);
            else 
                root = double_rotate_with_right(root);
        }
    }

    root->height = root_height(root);
    return root;
}
void print_tree(AvlNode *root, int space) {
    if (root == NULL)
        return;
    print_tree(root->right, space + 5);
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("%d:%d\n", root->value, root->height);
    print_tree(root->left, space + 5);
}

void test_avl_tree() {
    AvlNode *tree = insert(3, NULL);
    tree = insert(2, tree);
    printf("insert 3, 2:\n");
    print_tree(tree, 0);
    printf("insert 1, should do single rotate with right:\n");
    tree = insert(1, tree);
    print_tree(tree, 0);
    printf("insert 4\n");
    tree = insert(4, tree);
    print_tree(tree, 0);
    printf("insert 5, should do single rotate with left:\n");
    tree = insert(5, tree);
    print_tree(tree, 0);

    printf("insert 6, should do single rotate with left on root:\n");
    tree = insert(6, tree);
    print_tree(tree, 0);

    printf("insert 7, should do single rotate with left:\n");
    tree = insert(7, tree);
    print_tree(tree, 0);

    printf("insert 16:\n");
    tree = insert(16, tree);
    print_tree(tree, 0);

    printf("insert 15, should do double rotate:\n");
    tree = insert(15, tree);
    print_tree(tree, 0);
}

int main() {
    test_avl_tree();
}

