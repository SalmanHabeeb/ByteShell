#include <stdlib.h>
#include<stdio.h>
#include <error.h>
#include <unistd.h>

void exit_command(char **args) {
    exit(0);
}

void cd_command(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "byteshell: cd: missing argument\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("->cd");
        }
    }
}

void help_command(char **args) {
    char *helptext =
        "ByteShell - the Kinda Aimless Shell. "
        "The following commands are built in:\n"
        "  cd       Change the working directory.\n"
        "  exit     Exit the shell.\n"
        "  help     Print this help text.\n";
    printf("%s", helptext);
}