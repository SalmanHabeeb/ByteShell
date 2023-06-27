#include "llist.h"

#ifndef HISTORY_H_
#define HISTORY_H_

struct ListNode* get_history(char *path);
void show_history(char* start_path);
void write_history(struct ListNode* history, char* path);
void prepend_history(char* data, char* path);

#endif