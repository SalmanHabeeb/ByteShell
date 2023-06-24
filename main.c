#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
            history = prepend_history(history, line);
        }

        free(tokens);
        free(line);
    }
}