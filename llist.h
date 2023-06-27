#ifndef LLIST_H_
#define LLIST_H_
#define MAX_LLIST_LENGTH 300
struct ListNode {
    char* data;
    struct ListNode* next;
};
struct ListNode* create_node(const char* data);
struct ListNode* prepend_list(struct ListNode* head, const char* data);
struct ListNode* reverse_list(struct ListNode* head);
void display_list(struct ListNode* head);
void free_list(struct ListNode* head);
#endif