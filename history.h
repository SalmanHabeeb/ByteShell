#include "llist.h"

#ifndef HISTORY_H_
#define HISTORY_H_
void show_history(struct ListNode* history);
struct ListNode* get_history();
void write_history(struct ListNode* history, char* path);
struct ListNode* prepend_history(struct ListNode* history, char* data, char* path);
#endif