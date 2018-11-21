#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

void fatal_error(char *msg) {
    printf("fatal error: %s\n", msg);
    exit(1);
}

typedef struct Node {
    int value;
    struct Node *next;
} Node, *List;

List create_list() {
    List l = malloc(sizeof(Node));
    if (l == NULL)
        fatal_error("out of space");
    l->next = NULL;
    return l;
}

void free_list(List l) {
    if (l == NULL)
        return;
    Node *tmp;
    while (l != NULL) {
        tmp = l;
        l = l->next;
        free(tmp);
    }
}

void insert(int value, Node *prev) {
    Node *inserted = malloc(sizeof(Node));
    if (inserted == NULL)
        fatal_error("out of space");
    inserted->value = value;
    inserted->next = prev->next;
    prev->next = inserted;
}

Node *find(int value, List l) {
    l = l->next;
    while (l != NULL && l->value != value)
        l = l->next;
    return l;
}

Node *find_prev(int value, List l) {
    while (l->next != NULL && l->next->value != value)
        l = l->next;
    return l;
}

bool delete(int value, List l) {
    Node *prev = find_prev(value, l);
    if (prev->next == NULL)
        return false;
    Node *tmp = prev->next;
    prev->next = tmp->next;
    free(tmp);
    return true;
}

Node *find_last(List l) {
    while (l->next != NULL)
        l = l->next;
    return l;
}

void append(int value, List l) {
    l = find_last(l);
    insert(value, l);
}

void print_list(List l) {
    l = l->next;
    printf("List: H->");
    while (l != NULL) {
        printf("%d->", l->value);
        l = l->next;
    }
    printf("N\n");
}

void test_list() {

    List l = create_list();
    assert(l != NULL);
    printf("after create empty list: \n");
    print_list(l);

    printf("after insert 1 into list: \n");
    insert(1, l);
    assert(l->next->value == 1);
    print_list(l);

    printf("after append 2 into list: \n");
    append(2, l);
    assert(find_last(l)->value == 2);
    print_list(l);

    printf("after append 3 into list: \n");
    append(3, l);
    assert(find_last(l)->value == 3);
    print_list(l);

    printf("after delete nonexist 5 at list: \n");
    assert(delete(5, l) == false);
    print_list(l);

    printf("after delete 2 at list: \n");
    assert(delete(2, l) == true);
    assert(l->next->value == 1);
    assert(find_last(l)->value == 3);
    assert(find_last(l) == l->next->next);
    print_list(l);

    free_list(l);
}

int main() {
    test_list();
}
