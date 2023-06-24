#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"commands.h"
#include"executor.h"
#include"parse.h"
#include"llist.h"
#include"history.h"

void launch_shell();

int main() {
    launch_shell();
    return 0;
}

void launch_shell() {
    struct ListNode* history;
    #ifndef BUF_SIZE
    #define BUF_SIZE 64
    #endif
    char buffer[BUF_SIZE];
    char *p;

    p = getcwd(buffer, BUF_SIZE);
    // printf("%s", p);
    if (p == NULL) {
        perror("_getcwd");
        exit(EXIT_FAILURE);
    }
    history = get_history();
    while (true) {
        printf("$ ");
        char *line = shell_read_line();
        char **tokens = get_tokens(line);

        if (tokens[0] != NULL) {
            if(strcmp(tokens[0],"history") == 0) {
                show_history(history);
            } else  {
                run_shell_cmd(tokens);
            }
            history = prepend_history(history, line, p);
        }

        free(tokens);
        free(line);
    }
}