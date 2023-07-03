#include "executor.h"

#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../alias/alias.h"
#include "../commands/commands.h"
#include "../llist/llist.h"
#include "../lmap/lmap.h"
#include "../parse/parse.h"

struct inbuiltcmd inbuiltcmds[] = {
    {"help", help_command, "Print this help text"},
    {"show", show_license_command, "Show license"},
    {"exit", exit_command, "Exit this shell"},
    {"cd", cd_command, "Change the working directory"},
    {"alias", alias_command, "Set the alias"},
    {"unalias", unalias_command, "Remove alias"},
    {"history", history_command, "Show history"},
    {"ulimit", ulimit_command, "Handle system resources like in bash"},
};

int get_no_of_inbuilt_cmds() {
  return sizeof(inbuiltcmds) / sizeof(struct inbuiltcmd);
}

// copy string data from linked list to array and return it
char **copy(struct ListNode *head, int size) {
  // loop through the linked list and array simultaneously
  // allocate memory for array of char pointers
  char **array = (char **)malloc((size + 1) * sizeof(char *));
  if (array == NULL) {
    perror("Memory allocation failed");
    return NULL;
  }
  struct ListNode *current = head;
  int i = 0;
  while (current != NULL) {
    // copy string data from current node to current element of array
    *(array + i) = malloc(strlen(current->data) + 1);
    strcpy(*(array + i), current->data);
    // move to next node and next element
    current = current->next;
    i++;
  }
  *(array + i) = NULL;
  // return pointer to array
  return array;
}

void run_shell_cmd(struct ListNode *tokens, char *start_path) {
  int count = count_list(tokens);

  char **args = copy(tokens, count);
  if (args[1] != NULL) {
  }

  for (int i = 0; i < get_no_of_inbuilt_cmds(); i++) {
    if (strcmp(args[0], inbuiltcmds[i].name) == 0) {
      inbuiltcmds[i].func(args, start_path);
      for (int i = 0; i < count; i++) {
        free(*(args + i));
      }
      free(args);
      return;
    }
  }
  struct MapNode *alias = get_alias(args[0], start_path);
  if (alias != NULL) {
    struct ListNode *alias_tokens = get_tokens(alias->value, " \t\r\n");
    if (alias_tokens != NULL) {
      run_shell_cmd(alias_tokens, start_path);
      free_list(&alias_tokens);
      return;
    }
  }
  alias = NULL;

  pid_t child_pid = fork();

  if (child_pid == 0) {
    execvp(args[0], args);
    perror("byteshell");
    exit(1);
  } else if (child_pid > 0) {
    int status;
    do {
      waitpid(child_pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  } else {
    perror("byteshell");
  }
}