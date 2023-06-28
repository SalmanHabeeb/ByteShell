#include "executor.h"

#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "commands.h"

struct inbuiltcmd inbuiltcmds[] = {
    {"help", help_command, "Print this help text"},
    {"show", show_license_command, "Show license"},
    {"exit", exit_command, "Exit this shell"},
    {"cd", cd_command, "Change the working directory"},
};

int get_no_of_inbuilt_cmds() {
  return sizeof(inbuiltcmds) / sizeof(struct inbuiltcmd);
}

void run_shell_cmd(char **args, char *start_path) {
  for (int i = 0; i < get_no_of_inbuilt_cmds(); i++) {
    if (strcmp(args[0], inbuiltcmds[i].name) == 0) {
      inbuiltcmds[i].func(args);
      return;
    }
  }

  if (strcmp(args[0], "alias") == 0) {
    alias_command(args, start_path);
    return;
  } else if (strcmp(args[0], "unalias") == 0) {
    unalias_command(args, start_path);
    return;
  }

  if (strcmp(args[0], "history") == 0) {
    history_command(args, start_path);
    return;
  }

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