#include<stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include"commands.h"
#include"executor.h"
#include"parse.h"

void launch_shell();

int main() {
    launch_shell();
    return 0;
}

void launch_shell() {
    while (true) {
        printf("$ ");
        char *line = shell_read_line();
        char **tokens = get_tokens(line);

        if (tokens[0] != NULL) {
            run_shell_cmd(tokens);
        }

        free(tokens);
        free(line);
    }
}