/*
 * 主要实现了 binary serach tree 的 insert 和 delete
 * 这里实现的关键是，insert 和 delete 都要返回修改后的 root 值，因为我们可能将原有的指针设置为 NULL 或者分配新的 node
 */
#include <stdlib.h>
#include <stdio.h>

void fatal_error(char *msg) {
    printf("fatal error: %s\n", msg);
    exit(1);
}

typedef struct SearchNode {
    int value;
    struct SearchNode *left;
    struct SearchNode *right;
} SearchNode;

SearchNode *create_tree(int value) {
    SearchNode *node = malloc(sizeof(SearchNode));
    if (node == NULL)
        fatal_error("out of space");
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void free_tree(SearchNode *root) {
    if (root == NULL)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

// valid root
SearchNode *insert(int value, SearchNode *root) {
    if (root == NULL) {
        SearchNode *node = malloc(sizeof(SearchNode));
        if (node == NULL)
            fatal_error("out of space");
        node->value = value;
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    if (value < root->value)
        root->left = insert(value, root->left);
    else if(value > root->value)
        root->right = insert(value, root->right);
    // if exists, do nothing.
    return root;
}

// valid root
SearchNode *find_min(SearchNode *root) {
    if (root == NULL)
        return NULL;

    while (root->left) root = root->left;
    return root;
}

// valid root
SearchNode *delete(int value, SearchNode *root) {
    if (root == NULL)
        return NULL;

    if (value < root->value) {
        root->left = delete(value, root->left);
    } else if (value > root->value) {
        root->right = delete(value, root->right);
    // 如果两个孩子都存在，从右子树中找到最小的孩子，将自己的值设置为该孩子，然后从右子树中删除该孩子的值。
    // 如果只有一个孩子为 NULL，则将其设置为另一个孩子，并 free root。
    } else {
        if (root->left == NULL) {
            SearchNode *tmp = root;
            root = root->right;
            free(tmp);
        } else if (root->right == NULL) {
            SearchNode *tmp = root;
            root = root->left;
            free(tmp);
        } else {
            SearchNode *min_node = find_min(root->right);
            root->value = min_node->value;
            root->right = delete(min_node->value, root->right);
        }
    }
    return root;
}

// other implmentation
SearchNode *delete2(int value, SearchNode *root) {
    if (root == NULL)
        return NULL;

    if (value < root->value) {
        root->left = delete(value, root->left);
    } else if (value > root->value) {
        root->right = delete(value, root->right);
    // 如果两个孩子都存在，从右子树中找到最小的孩子，将自己的值设置为该孩子，然后从右子树中删除该孩子的值。
    // 如果只有一个孩子为 NULL，则将其设置为另一个孩子，并 free root。
    } else {
        if (root->left && root->right) {
            SearchNode *min_node = find_min(root->right);
            root->value = min_node->value;
            root->right = delete(min_node->value, root->right);
        } else {
            SearchNode *tmp = root;
            root = root->left? root->left: root->right;
            free(tmp);
        }
    }
    return root;
}


void print_tree(SearchNode *root, int space) {
    if (root == NULL)
        return;

    print_tree(root->right, space + 5);

    for (int i = 0; i < space; i++)
        printf(" ");
    printf("%d\n", root->value);

    print_tree(root->left, space + 5);
}

void test_binary_search_tree_adt() {
    printf("create tree:\n");
    SearchNode *tree = create_tree(6);
    print_tree(tree, 0);

    printf("insert value:\n");
    insert(6, tree);
    insert(8, tree);
    insert(2, tree);
    insert(1, tree);
    insert(4, tree);
    insert(3, tree);
    print_tree(tree, 0);
    printf("delete non exist value 100:\n");
    delete(100, tree);
    print_tree(tree, 0);

    printf("insert value 5:\n");
    insert(5, tree);
    print_tree(tree, 0);

    printf("delete value 5:\n");
    tree = delete(5, tree);
    print_tree(tree, 0);

    printf("delete value 4:\n");
    tree = delete(4, tree);
    print_tree(tree, 0);

    printf("delete value 3:\n");
    tree = delete(3, tree);
    print_tree(tree, 0);

    printf("insert value 5, 3, 4:\n");
    insert(5, tree);
    insert(3, tree);
    insert(4, tree);
    print_tree(tree, 0);

    printf("delete value 2:\n");
    tree = delete(2, tree);
    print_tree(tree, 0);
}

void test_binary_search_tree_adt_with_delete2() {
    printf("create tree:\n");
    SearchNode *tree = create_tree(6);
    print_tree(tree, 0);

    printf("insert value:\n");
    insert(6, tree);
    insert(8, tree);
    insert(2, tree);
    insert(1, tree);
    insert(4, tree);
    insert(3, tree);
    print_tree(tree, 0);
    printf("delete2 non exist value 100:\n");
    delete2(100, tree);
    print_tree(tree, 0);

    printf("insert value 5:\n");
    insert(5, tree);
    print_tree(tree, 0);

    printf("delete2 value 5:\n");
    tree = delete2(5, tree);
    print_tree(tree, 0);

    printf("delete2 value 4:\n");
    tree = delete2(4, tree);
    print_tree(tree, 0);

    printf("delete2 value 3:\n");
    tree = delete2(3, tree);
    print_tree(tree, 0);

    printf("insert value 5, 3, 4:\n");
    insert(5, tree);
    insert(3, tree);
    insert(4, tree);
    print_tree(tree, 0);

    printf("delete2 value 2:\n");
    tree = delete2(2, tree);
    print_tree(tree, 0);
}


int main() {
    test_binary_search_tree_adt();
    printf("\n\ntest_binary_search_tree_adt_with_delete2:\n");
    test_binary_search_tree_adt_with_delete2();
}


