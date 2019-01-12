/*
 * 错误原因:
 * 1. get_and_move(struct ListNode **l) 的参数应该为 **l, 我写成了 *l 
 * /
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

// int get_and_move(struct ListNode *l) {
int get_and_move(struct ListNode **l) {
    if ((*l) == NULL)
        return 0;
    int value = (*l)->val;
    *l = (*l)->next;
    return value;
}


struct ListNode *allocate(int value) {
    struct ListNode *node = malloc(sizeof(struct ListNode));
    if (node == NULL)
        exit(1);
    node->val = value;
    node->next = NULL;
    return node;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode *head = NULL;
    struct ListNode **tail_ptr = &head;
    int carry = 0;
    int sum;
    while (l1 || l2) {
        sum = get_and_move(&l1) + get_and_move(&l2) + carry;
        carry = sum / 10;
        sum %= 10;
        
        *tail_ptr = allocate(sum);
        tail_ptr = &((*tail_ptr)->next);
    }
    if (carry)
        *tail_ptr = allocate(1);
    return head;
}
