#include "llist.h"

#ifndef EXECUTOR_H_
#define EXECUTOR_H_
struct inbuiltcmd {
  char *name;
  void (*func)(char **args, char *start_path);
  char *description;
};

int get_no_of_inbuilt_cmds();
void run_shell_cmd(struct ListNode *tokens, char *start_path);
#endif