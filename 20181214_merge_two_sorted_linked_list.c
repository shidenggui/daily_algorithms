/*
 * 合并两个有序链表，关键点在于在开始的时候，如果合并中的某个 list 为 NULL 时不需要移动到到实际 node 的位置。
 * 即在被合并的 list 头结点不为 NULL 时才移动到实际节点。
 * 测试用例:
 * 1. 两个 NULL 链表
 * 2. 一个 NULL，一个空链表
 * 3. 两个空链表
 * 3. 两个带一个节点的链表
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

List create_list() {
    List li = malloc(sizeof(Node));
    if (li == NULL)
        fatal_error("out of space");
    li->next = NULL;
    return li;
}

void free_list(List li) {
    if (li == NULL)
        return;

    Node *tmp;
    while (li) {
        tmp = li;
        li = li->next;
        free(tmp);
    }
}

void print_list(List li) {
    if(li == NULL) {
        printf("N\n");
        return;
    }

    printf("H->");
    li = li->next;
    while (li) {
        printf("%d->", li->value);
        li = li->next;
    }
    printf("N\n");
}

void insert(int value, Node *prev) {
    if (prev == NULL)
        return;

    Node *inserted = malloc(sizeof(Node));
    if (inserted == NULL)
        fatal_error("out of space");
    inserted->value = value;
    inserted->next = prev->next;
    prev->next = inserted;
}


List merge_sorted_list(List l1, List l2) {
    if (l1 != NULL)
        l1 = l1->next;
    if (l2 != NULL)
        l2 = l2->next;

    List li = create_list();
    Node *prev = li;
    while (l1 && l2) {
        if (l1->value <= l2->value) {
            insert(l1->value, prev);
            l1 = l1->next;
        } else {
            insert(l2->value, prev);
            l2 = l2->next;
        }
        prev = prev->next;
    }

    Node *remain = l1 ? l1: l2;

    while (remain) {
        insert(remain->value, prev);
        remain = remain->next;
        prev = prev->next;
    }
    return li;
}

void test_merge_sorted_list() {
    printf("merge two null list should return empty list:");
    List l = merge_sorted_list(NULL, NULL);
    print_list(l);

    List l1 = create_list();
    printf("merge empty list should return empty list:");
    free_list(l);
    l = merge_sorted_list(l1, NULL);
    print_list(l);

    printf("merge one empty list should return the other's copy:\n");
    printf("not empty list: ");
    insert(7, l1);
    insert(5, l1);
    insert(3, l1);
    insert(1, l1);
    print_list(l1);
    printf("after merge:\n");
    free_list(l);
    l = merge_sorted_list(l1, NULL);
    print_list(l);


    printf("merge two list:\n");
    List l2 = create_list();
    insert(8, l2);
    insert(6, l2);
    insert(4, l2);
    insert(2, l2);
    printf("list 1: ");
    print_list(l1);
    printf("list 2: ");
    print_list(l2);
    printf("after merge:");
    free_list(l);
    l = merge_sorted_list(l1, l2);
    print_list(l);

    free_list(l1);
    free_list(l2);
}

int main() {
    test_merge_sorted_list();
}
