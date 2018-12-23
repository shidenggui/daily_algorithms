/*
 * 找出两个单向链表的第一个公共节点。
 * 思路：
 * 遍历计算出两个链表的长度，然后使一个指针指向长链表，一个指针指向短链表，根据它们的 diff，让长链表先走 diff 步，
 * 然后同时走直到两个指针相等为止，然后返回。
 * 如果不存在，则最后两个指针都会等于 NULL，然后返回 NULL。
 */
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

// valid list
int list_len(List l);

Node *first_common_node_of_lists(List l1, List l2) {
    if (!l1 || !l2) 
        return NULL;
    int l1_len = list_len(l1);
    int l2_len = list_len(l2);
    int diff = l1_len - l2_len;

    Node *long_list = l1;
    Node *short_list = l2;
    if (diff < 0) {
        long_list = l2;
        short_list = l1;
        diff = -diff;
    }

    for (int i = 0; i < diff; i++)
        long_list = long_list->next;
    while (long_list != short_list) {
        long_list = long_list->next;
        short_list = short_list->next;
    }
    return long_list;
}

int list_len(List l) {
    int len = 0;
    while (l->next) {
        len++;
        l = l->next;
    }
    return len;
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
