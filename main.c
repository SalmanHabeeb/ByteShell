#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commands.h"
#include "executor.h"
#include "history.h"
#include "llist.h"
#include "parse.h"

#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

void launch_shell();

int main() {
  launch_shell();
  return 0;
}

void launch_shell() {
  struct ListNode *history;
#ifndef BUF_SIZE
#define BUF_SIZE 64
#endif
  char *start_path = malloc(BUF_SIZE);

  getcwd(start_path, BUF_SIZE);
  if (start_path == NULL) {
    perror("_getcwd");
    exit(EXIT_FAILURE);
  }
  while (true) {
    char *curr_path = malloc(BUF_SIZE);

    getcwd(curr_path, BUF_SIZE);
    if (curr_path == NULL) {
      perror("_getcwd");
      exit(EXIT_FAILURE);
    }

    printf(ANSI_COLOR_CYAN "%s: " ANSI_COLOR_RESET "$ ", curr_path);

    char *line = shell_read_line();
    char *history_line = malloc(strlen(line));

    strcpy(history_line, line);
    strtok(history_line, "\n");

    char **tokens = get_tokens(line);

    if (tokens[0] != NULL) {
      run_shell_cmd(tokens, start_path);
      prepend_history(history_line, start_path);
    }

    free(tokens);
    free(line);
    free(history_line);
    free(curr_path);
  }

  free(start_path);
}