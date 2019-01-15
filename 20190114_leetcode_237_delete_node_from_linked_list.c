/*
 * 思路：因为不考虑删除尾部，所以直接拷贝后面的值即可
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
typedef struct ListNode Node;
void deleteNode(Node* node) {
    node->val = node->next->val;
    Node *deleted = node->next;
    node->next = deleted->next;
    free(deleted);
}
