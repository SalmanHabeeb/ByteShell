#ifndef COMMANDS_H_
#define COMMANDS_H_
void exit_command();
void cd_command(char **args, char *start_path);
void help_command(char **args, char *start_path);
void history_command(char **args, char *start_path);
void show_license_command(char **args, char *start_path);
void alias_command(char **args, char *start_path);
void unalias_command(char **args, char *start_path);
void ulimit_command(char **args, char *start_path);
#endif