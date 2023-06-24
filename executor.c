#include<string.h>
#include<sys/wait.h>
#include<stdio.h>
#include<error.h>
#include<stdlib.h>
#include <unistd.h>
#include"commands.h"


#include "executor.h"

struct inbuiltcmd inbuiltcmds[] = {
    {"help", help_command, "Print this help text"},
    {"show", show_license_command, "Show license"},
    {"exit", exit_command, "Exit this shell"},
    {"cd", cd_command, "Change the working directory"},
};

int get_no_of_inbuilt_cmds() {
    return sizeof(inbuiltcmds) / sizeof(struct inbuiltcmd);
}

void run_shell_cmd(char **args) {
    for (int i = 0; i < get_no_of_inbuilt_cmds(); i++) {
        if (strcmp(args[0], inbuiltcmds[i].name) == 0) {
            inbuiltcmds[i].func(args);
            return;
        }
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