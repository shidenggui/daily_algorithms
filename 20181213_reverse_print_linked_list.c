#include <stdlib.h>
#include <stdio.h>
typedef struct Node {
    int value;
    struct Node *next;
} Node, *List;

void print_node(Node *node) {
    if (node == NULL) {
        printf("N->");
        return;
    }
    print_node(node->next);
    printf("%d->", node->value);
}

void reverse_print(List li) {
    print_node(li->next);
    printf("H");
}

void test_reverse_print() {
    Node tail = {.value=2, .next=NULL};
    Node next_to_tail = {.value=1, .next=&tail};
    List li = &(Node){.next=&next_to_tail};
    reverse_print(li);
}

int main() {
    test_reverse_print();
}


