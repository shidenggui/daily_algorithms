/*
 * https://leetcode.com/problems/remove-linked-list-elements/
 * 从 linked list 中移除指定值
 * 例如 1->N  移除 1 返回 N
 * 1->2-1->N 移除 1 返回 2->N
 * 思路：
 * 因为可能改变头结点，所以先将 head 可能等于 val 的节点都移除，直到 head 不为 val 为止，
 * 如果此时 head 为 NULL，直接返回。否则的话后面 head 节点就不会改变了。
 * 然后后面就变成了经典的从 linked list 中删除一个节点的情况，这里需要用到一个待删除节点的 prev 指针，所以使得 prev = head, cur = head->next，后面就是通常的逻辑了。
 * 唯一需要注意的是，但 cur 节点 = val 被删除时，cur = cur->next，但是 prev 不需要移动
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
typedef struct ListNode Node;
struct ListNode* removeElements(Node* head, int val) {
    if (!head)
        return NULL;

    Node *tmp;
    while (head && head->val == val) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    if (!head)
        return NULL;

    Node *prev = head;
    Node *cur = head->next;
    while (cur) {
        if (cur->val == val) {
            tmp = cur;
            prev->next = cur->next;
            cur = cur->next;
            free(tmp);
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
    return head;

}
