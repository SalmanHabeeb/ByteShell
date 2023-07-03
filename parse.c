#include "parse.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "llist.h"

struct ListNode *get_tokens(char *line, char *delimiters) {
  struct ListNode *tokens = NULL;

  char *token = strtok(line, delimiters);

  while (token != NULL) {
    tokens = prepend_list(tokens, token);
    token = strtok(NULL, delimiters);
  }
  tokens = reverse_list(tokens);
  return tokens;
}

char *concat_tokens(char **tokens, char *delimiter) {
  // check if the arguments are valid
  if (tokens == NULL || delimiter == NULL) {
    return NULL;
  }

  // check if the tokens array is empty
  if (tokens[0] == NULL) {
    return NULL;
  }

  // calculate the total length of the concatenated string
  int i = 0;
  int len = 0;
  while (tokens[i] != NULL) {
    // fprintf(stderr, "%s, %d", *(tokens + i), i);
    len += strlen(tokens[i]);

    len++;  // for the delimiter
    i++;
  }

  // allocate memory for the result
  char *result = malloc(len + 1);
  if (result == NULL) {
    return NULL;
  }

  // copy the first token to the result
  strcpy(result, tokens[0]);

  // append the rest of the tokens with the delimiter to the result
  for (int j = 1; j < i; j++) {
    strcat(result, delimiter);
    strcat(result, tokens[j]);
  }

  // return the result
  return result;
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