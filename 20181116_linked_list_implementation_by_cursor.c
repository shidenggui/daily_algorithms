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
    int next;
} Node; 

// int *arr; Should be the array of struct Node
Node *arr;

void initialize_array(int size) {
    arr = malloc(sizeof(Node) * size);
    if (arr == NULL)
        fatal_error("out of space");
    for (int i = 0; i < size - 1; i++)
        arr[i].next = i + 1;
    arr[size - 1].next = 0;
    /*
    for (int i = 0; i < size - 1; i++)
        arr[i] = i + 1; // arr[i] is Node struct, can't manipuldate directly
    arr[size - 1] = 0;
    */
}

void free_array() {
    if (arr == NULL)
        return;
    free(arr);
}

int list_malloc() {
    int node = arr[0].next;
    arr[0].next = arr[node].next;
    return node;
}

void list_free(int node) {
    arr[node].next = arr[0].next;
    arr[0].next = node;
}

int create_list() {
    int head = list_malloc();
    if (head == 0)
        fatal_error("out of space");
    arr[head].next = 0;
    return head;
}

void free_list(int l) {
    while (l != 0) {
        int tmp = l;
        l = arr[l].next;
        list_free(tmp);
    }
}

void insert(int value, int prev) {
    int inserted = list_malloc();
    if (inserted == 0)
        fatal_error("out of space");
    arr[inserted].value = value;
    arr[inserted].next = arr[prev].next;
    arr[prev].next = inserted;
}

int find_prev(int value, int l) {
    while (arr[l].next != 0 && arr[arr[l].next].value != value)
        l = arr[l].next;
    return l;
}

bool delete(int value, int l) {
    int prev = find_prev(value, l);
    // if(prev == 0)
    // when find_prev not found, should judge by arr[prev].next == 0, not prev == 0, becase in linked list with head, find_prev's prev always != 0
    if (arr[prev].next == 0)
        return false;
    int tmp = arr[prev].next;
    arr[prev].next = arr[tmp].next;
    list_free(tmp);
    return true;
}

int find_last(int l) {
    while (arr[l].next != 0)
        l = arr[l].next;
    return l;
}

void append(int value, int l) {
    // could use linked list with last pointer to speed up append
    int last = find_last(l);
    insert(value, last);
}

void print_list(int l) {
    printf("List: %d H->", l);
    l = arr[l].next;
    while (l != 0) {
        printf("%d->", arr[l].value);
        l = arr[l].next;
    }
    printf("N\n");
}

void print_array(Node *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", i);
        printf("%d ", arr[i].value);
        printf("%d \n", arr[i].next);
    }
}

void test_list() {
    int size = 10;
    initialize_array(size);
    printf("global array: \n");
    print_array(arr, size);

    int l = create_list();
    assert(l != 0);
    printf("after create empty list: \n");
    print_array(arr, size);
    print_list(l);

    printf("after insert 1 into list: \n");
    insert(1, l);
    assert(arr[arr[l].next].value == 1);
    print_array(arr, size);
    print_list(l);

    printf("after append 2 into list: \n");
    append(2, l);
    assert(arr[find_last(l)].value == 2);
    print_array(arr, size);
    print_list(l);

    printf("after append 3 into list: \n");
    append(3, l);
    assert(arr[find_last(l)].value == 3);
    print_array(arr, size);
    print_list(l);

    printf("after delete nonexist 5 at list: \n");
    assert(delete(5, l) == false);
    print_array(arr, size);
    print_list(l);

    printf("after delete 2 at list: \n");
    assert(delete(2, l) == true);
    assert(arr[arr[l].next].value == 1);
    assert(arr[find_last(l)].value == 3);
    assert(find_last(l) == arr[arr[l].next].next);
    print_array(arr, size);
    print_list(l);

    free_array();
}

int main() {
    test_list();
}
