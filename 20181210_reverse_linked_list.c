#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void fatal_error(char *msg) {
    printf("fatal error: %s\n", msg);
    exit(1);
}

typedef struct Node {
    int value;
    struct Node *next;
} Node, *List;

void reverse(List li) {
    Node *prev = NULL;
    Node *cur = li->next;
    while (cur) {
        Node *tmp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = tmp;
    }
    li->next = prev;
}

void reverse_by(Node *p, Node *q) {
    Node *prev = p;
    Node *cur = p->next;
    while (prev != q) {
        Node *tmp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = tmp;
    }
}

void print_list(List li) {
    printf("H->");
    li = li->next;
    while (li) {
        printf("%d->", li->value);
        li = li->next;
    }
    printf("N\n");
}

void insert(int value, Node *prev) {
    Node *inserted = malloc(sizeof(Node));
    if (inserted == NULL)
        fatal_error("out of space");
    inserted->value = value;
    inserted->next = prev->next;
    prev->next = inserted;
}

void test_reverse() {
    List li = &(Node){.value=1, .next=NULL};
    print_list(li);
    printf("reverse list: \n");
    reverse(li);
    print_list(li);

    insert(3, li);
    insert(2, li);
    insert(1, li);

    assert(li->next->value == 1);
    assert(li->next->next->value == 2);
    assert(li->next->next->next->value == 3);
    print_list(li);

    printf("reverse list: \n");
    reverse(li);

    assert(li->next->value == 3);
    assert(li->next->next->value == 2);
    assert(li->next->next->next->value == 1);
    print_list(li);
}

int main() {
    test_reverse();
}
