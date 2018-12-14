/*
 * 从链表中删除倒数第 k 个元素
 * 思路：
 * 用一个快指针先走 k 步，然后一个慢指针后走。
 * 关键点在于快指针到达 NULL 时，慢指针需要处于倒数第 k + 1 个元素，此时才可以删除后面的第 k 个元素。
 * 如何避免出错，思考有一个 Node 的 list，H->v1->N，然后需要删除的 k 为 1。
 * 还要注意的时可能链表没有倒数第 k 项，这是需要使用变量 i 记录 fast 指针移动了多远，如果不满 k 步则说明指针长度不够，直接返回。
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

void print_list(List li) {
    if (li == NULL) {
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

void delete_kth_to_last(List li, unsigned k) {
    if (li == NULL)
        return;
    if (k <= 0)
        return;

    Node *fast = li->next;
    int i = 0;
    while (fast != NULL && i < k) {
        fast = fast->next;
        i++;
    }
    if (i != k)
        return;

    Node *slow = li;
    while (fast != NULL) {
        fast = fast->next;
        slow = slow->next;
    }

    Node *tmp = slow->next;
    slow->next = tmp->next;
    free(tmp);
}

void test_delete_kth_to_last() {
    List li = create_list();
    printf("init: ");
    print_list(li);

    printf("delete kth node from li\n");
    delete_kth_to_last(li, 1);
    delete_kth_to_last(li, 2);
    printf("Still alive, congratulation!\n");

    printf("insert value to list:\n");
    insert(1, li);
    print_list(li);

    printf("delete last node from list:\n");
    delete_kth_to_last(li, 1);
    print_list(li);

    printf("insert some values to list:\n");
    insert(2, li);
    insert(1, li);
    print_list(li);

    printf("delete not exist kth from list:\n");
    delete_kth_to_last(li, 10);
    printf("Still aliva!\n");
    
    printf("delete all node from list:\n");
    delete_kth_to_last(li, 2);
    print_list(li);
    delete_kth_to_last(li, 1);
    print_list(li);
}

int main() {
    test_delete_kth_to_last();
}
