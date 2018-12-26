#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void fatal_error(char *msg) {
    printf("%s\n", msg);
    exit(1);
}

typedef struct Node {
    int value;
    struct Node *next;
} Node, *List;

List create_list() {
    List li = malloc(sizeof(Node));
    if (li == NULL)
        fatal_error("out of space");
    li->next = NULL;
    return li;
}

Node* insert(int value, Node *prev) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL)
        fatal_error("out of space");
    node->value = value;
    node->next = prev->next;
    prev->next = node;
    return node;
}

void link(Node *node, Node *prev) {
    node->next = prev->next;
    prev->next = node;
}

void print_list(List li) {
    printf("H->");
    li = li->next;
    while (li) {
        printf("%x:%d->", li, li->value);
        li = li->next;
    }
    printf("N\n");
}

int len(List l) {
    int n = 0;
    while(l->next) {
        n++;
        l = l->next;
    }
    return n;
}

Node *first_common_node_of_lists(List l1, List l2) {
    if (!l1 || !l2)
        return NULL;

    int l1_len = len(l1);
    int l2_len = len(l2);
    int diff = l1_len - l2_len;
    List long_list = l1;
    List short_list = l2;
    if (diff < 0) {
        long_list = l2;
        short_list = l1;
        diff = -diff;
    }
    for (int i = 0; i < diff; i++) long_list = long_list->next;
    while (long_list != short_list) {
        long_list = long_list->next;
        short_list = short_list->next;
    }
    return long_list;
}

void free_list(List l1, List l2) {
    Node *common = first_common_node_of_lists(l1, l2);
    while (l1 != common) {
        Node *tmp = l1;
        l1 = l1->next;
        free(tmp);
    }

    while (l2 != common) {
        Node *tmp = l2;
        l2 = l2->next;
        free(tmp);
    }

    while (common) {
        Node *tmp = common;
        common = common->next;
        free(tmp);
    }
}

void test_first_common_node_of_lists() {
    List l1 = create_list();
    List l2 = create_list();
    Node *last = insert(2, l1);
    Node *first = insert(1, l1);
    l2->next = first;
    print_list(l1);
    print_list(l2);
    assert(first_common_node_of_lists(l1, l2) == first);

    printf("l2 insert more node\n");
    insert(4, l2);
    print_list(l1);
    print_list(l2);
    assert(first_common_node_of_lists(l1, l2) == first);
    // unable to free
    free_list(l1, l2);
}

int main() {
    test_first_common_node_of_lists();
}
