#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include"parse.h"

#ifndef GROWTH_FACTOR
#define GROWTH_FACTOR 1.5
#endif

char **get_tokens(char *line) {
    int length = 0;
    int capacity = 16;

    char **tokens = calloc(capacity, sizeof(char*));
    if (!tokens) {
        perror("byteshell");
        exit(1);
    }

    char *delimiters = " \t\r\n";
    char *token = strtok(line, delimiters);

    while (token != NULL) {
        tokens[length] = token;
        length++;

        if (length >= capacity) {
            capacity = capacity * GROWTH_FACTOR;
            tokens = realloc(tokens, capacity * sizeof(char*));
            if (!tokens) {
                perror("byteshell");
                exit(1);
            }
        }

        token = strtok(NULL, delimiters);
    }

    return tokens;
}


char *shell_read_line() {
    char *line = NULL;
    size_t buflen = 0;
    errno = 0;
    ssize_t strlen = getline(&line, &buflen, stdin);
    if (strlen < 0) {
        if (errno) {
            perror("byteshell");
        }
        exit(1);
    }
    return line;
}