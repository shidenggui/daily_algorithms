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

typedef struct CircleStruct {
    int length;
    Node *head;
} CircleStruct, *Circle;

Circle create_circle(unsigned size) {
    if (size <= 0)
        fatal_error("size must larget than zero");
    Circle c = malloc(sizeof(CircleStruct));
    if (c == NULL)
        fatal_error("out of space");
    c->length = size;

    c->head = malloc(sizeof(Node));
    if (c->head == NULL)
        fatal_error("out of space");
    c->head->value = 0;
    c->head->next = NULL;

    Node *head = c->head;
    for (int i = 1; i < size; i++) {
        head->next = malloc(sizeof(Node));
        if (head->next == NULL)
            fatal_error("out of space");
        head = head->next;
        head->value = i;
        head->next = NULL;
    }
    head->next = c->head;
    return c;
}

// 从 head 的下一个节点开始删除，直到遇到 head 为止，然后 free head
void free_circle(Circle c) {
    Node *ptr = c->head->next;
    while (ptr != c->head) {
        Node *tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    free(c->head);
    free(c);
}

void delete(int k, Circle c) {
    // 这边需要获取需要删除的节点的前一个节点
    // 本身 c->head 就在 k = 1 的位置，所以移动到删除的节点需要 k - 1 步
    // 比如 k = 1，则需要移动的步伐为 k - 1 为 0
    // 同时在链表中删除需要移动到待删除节点的前一个节点，所以为 k - 2
    // 而且如果此时 k = 1 的话，k - 2 就是 - 1，所以额外加上 c->length 在取模
    // 防止出现负数
    int steps = (c->length + k - 2) % c->length;
    Node *prev = c->head;
    for (int i = 0; i < steps; i++)
        prev = prev->next;
    Node *tmp = prev->next;
    prev->next = tmp->next;
    free(tmp);
    c->head = prev->next;
    c->length--;
}

int last_remain(int n, int k) {
    Circle c = create_circle(n);
    while (c->length != 1)
        delete(k, c);
    int result = c->head->value;
    free_circle(c);
    return result;
}

void test_last_remain() {
    assert(last_remain(5, 3) == 3);
    assert(last_remain(4, 3) == 0);
}

int main() {
    test_last_remain();
}
