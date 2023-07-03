#ifndef ULIMIT_H_
#define ULIMIT_H_

void print_limit(int resource, char *name);
void set_limit(int resource, char *name, long value);
void show_all_limits();
void show_limit(char option);
void set_limit_option(char option, long value);

#endif