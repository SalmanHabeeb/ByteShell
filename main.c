#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "commands.h"

struct inbuiltcmd inbuiltcmds[] = {
    {"help", help_command},
    {"exit", exit_command},
    {"cd", cd_command},
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
        perror("kash");
        exit(1);
    } else if (child_pid > 0) {
        int status;
        do {
            waitpid(child_pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    } else {
        perror("kash");
    }
}

char **get_tokens(char *line) {
    int length = 0;
    int capacity = 16;

    char **tokens = malloc(capacity * sizeof(char *));
    if (!tokens) {
        perror("kash");
        exit(1);
    }

    char *delimiters = " \t\r\n";
    char *token = strtok(line, delimiters);

    while (token != NULL) {
        tokens[length] = token;
        length++;

        if (length >= capacity) {
            capacity = (int)(capacity * 1.5);
            tokens = realloc(tokens, capacity * sizeof(char *));
            if (!tokens) {
                perror("kash");
                exit(1);
            }
        }

        token = strtok(NULL, delimiters);
    }

    tokens[length] = NULL;
    return tokens;
}

char *shell_read_line() {
    char *line = NULL;
    size_t buflen = 0;
    errno = 0;
    ssize_t strlen = getline(&line, &buflen, stdin);
    if (strlen < 0) {
        if (errno) {
            perror("kash");
        }
        exit(1);
    }
    return line;
}

int main() {
    while (true) {
        printf("> ");
        char *line = shell_read_line();
        char **tokens = get_tokens(line);

        if (tokens[0] != NULL) {
            run_shell_cmd(tokens);
        }

        free(tokens);
        free(line);
    }
}