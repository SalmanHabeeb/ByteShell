#include <stdlib.h>
#include<stdio.h>
#include <error.h>
#include <unistd.h>
#include<string.h>

#include"history.h"

void exit_command(char **args) {
    exit(0);
}

void cd_command(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "byteshell: cd: missing argument\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("byteshell");
        }
    }
}

void help_command(char **args) {
    char *helptext =
        "ByteShell\n"
        "The following commands are built in:\n"
        "  cd       Change the working directory.\n"
        "  exit     Exit the shell.\n"
        "  help     Print this help text.\n"
        "  show     Print the license\n"
        "It can fork and run other commands\n";
    printf("%s", helptext);
}

void show_license_command(char **args) {
    if(args[1] == NULL || (strcmp("--l", args[1]) != 0 &&  strcmp("--mini", args[1]) != 0)) {
        fprintf(stderr, "show command.\nUse show with following parameters:\n\
         --l - show license\n\
         --mini - show copyright statement\n");
        return;
    }
    FILE *file;

    if (strcmp("--l", args[1]) == 0) {
        file = fopen("LICENSE", "r");
    } else {
        file = fopen("copyright.txt", "r");
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    printf("\n");
    fclose(file);
}

void history_command(char **args, char *start_path) {
    show_history(start_path);
}