/*
 * https://leetcode.com/problems/reverse-linked-list/
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseList(struct ListNode* head) {
    if (!head)
        return NULL;
    struct ListNode *prev = NULL;
    struct ListNode *cur = head;
    struct ListNode *tmp;
    while (cur) {
        tmp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = tmp;
    }
    return prev;
}
