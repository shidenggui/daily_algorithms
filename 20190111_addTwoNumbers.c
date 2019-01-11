/*
 * https://leetcode.com/problems/add-two-numbers/submissions/
 * test cases 真的非常有用，可以揪出很多小 bug。
 * 我现在发现我 while 的时候经常忘记写 make progress 的递进循环的条件，下次如果有递进的，使用 for
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode Node;
typedef Node *List;

void fatal_error(char *msg) {
    printf("fatal error: %s\n", msg);
    exit(1);
}

Node *allocate(int value) {
    Node *node = malloc(sizeof(Node));
    if (!node)
        fatal_error("out of space");
    node->val = value;
    node->next = NULL;
    return node;
}

int get_and_move(List *l) {
    if (*l == NULL)
        return 0;

    int val = (*l)->val;
    *l = (*l)->next;
    return val;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    if (!l1 && !l2)
        return NULL;

    List sum = NULL;
    // tail 为指向 List 尾部的指针，这样就不需要额外处理 head 为 NULL 的情况，非常巧妙
    List *tail = &sum;
    int carry = 0;
    int tmp;

    while (l1 || l2) {
        // 通过对 get_and_move 抽象来统一处理 l1 或者 l2 为 NULL 的情况
        int l1_val = get_and_move(&l1);
        int l2_val = get_and_move(&l2);
        tmp = l1_val + l2_val + carry;

        carry = tmp / 10;
        tmp %= 10;

        *tail = allocate(tmp);
        tail = &((*tail)->next);
    }

    if (carry)
        *tail = allocate(1);
    return sum;
}

