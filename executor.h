#ifndef EXECUTOR_H_
#define EXECUTOR_H_
struct inbuiltcmd {
    char *name;
    void (*func)(char **args);
};

int get_no_of_inbuilt_cmds();
void run_shell_cmd(char **args);
#endif