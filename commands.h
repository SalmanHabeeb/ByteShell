#ifndef COMMANDS_H_
#define COMMANDS_H_
struct inbuiltcmd {
    char *name;
    void (*func)(char **args);
};
void exit_command();
void cd_command(char **args);
void help_command(char **args);
#endif