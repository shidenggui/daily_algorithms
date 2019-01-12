/*
 * 反向打印 linked list，直接用递归即可，类似 postorder visit。
 * 这里比较有意思的是用一个数组构建出一个 linked list
 * 果然没有头结点的 list 就是用 Node ** 来搞定，这个抽象确实也非常不错，就是多了一层，写起来繁琐了一点
 */
#include <stdlib.h>
#include <stdio.h>


void fatal_error(char *msg) {
    printf("fatal error: %s\n", msg);
    exit(1);    
}

typedef struct Node {
    int value;
    struct Node *next;
} Node, *List;

void print(List head) {
    if (!head)
        return;
    print(head->next);
    printf("%d->", head->value);
}

void create_list(int *arr, int n, int idx, Node **root_ptr) {
    if (idx == n) {
        *root_ptr = NULL;
        return;
    }

    Node *node = malloc(sizeof(Node));
    if (node == NULL)
        fatal_error("out of space");
    node->value = arr[idx];
    create_list(arr, n, idx + 1, &(node->next));
    *root_ptr = node;
}

void print_list(List l) {
    while (l) {
        printf("%d->", l->value);
        l = l->next;
    }
    printf("N\n");
}

void test_print() {
    List l = NULL;
    create_list((int*)&(int[]){1, 2, 3, 4, 5}, 5, 0, &l);
    print_list(l);
    print(l);
}

int main() {
    test_print();
}
