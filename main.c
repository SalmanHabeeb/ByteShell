#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commands.h"
#include "executor.h"
#include "history.h"
#include "llist.h"
#include "parse.h"

#define ANSI_COLOR_CYAN "\x1b[36m\x1b[1m"
#define ANSI_COLOR_RESET "\x1b[0m"

void launch_shell();

extern char **environ;

int main() {
  launch_shell();
  return 0;
}

int setup_config(char *file_name, char **path_font, char **text_font) {
  FILE *file;          // This is your file stream
  char buffer[256];    // This is a buffer to store each line of the file
  char *name, *value;  // These are pointers to store the name and value of each
                       // directive

  file = fopen(file_name, "r");  // This will open your config file for reading
  if (file == NULL) {            // Check if the file is NULL
    return -1;                   // Return an error code
  }

  while (fgets(buffer, sizeof(buffer), file) !=
         NULL) {  // Loop until the end of the file
    if (buffer[0] ==
        '#') {  // If the first character is #, skip this line as a comment
      continue;
    }
    if (sscanf(buffer, "%m[^=]=%m[^\n]", &name, &value) ==
        2) {  // Parse the name and value using sscanf
      // The %m modifier allocates memory for the matched string
      // The [^=] and [^\n] match any character except = and newline
      if (strcmp(name, "PATH_FONT") == 0) {  // If the name is PATH_COLOR
        free(*path_font);
        *path_font = malloc(strlen(value) + 1);
        strcpy(*path_font, value);
      } else if (strcmp(name, "START_PATH") == 0) {
        if (chdir(value) != 0) {
          perror("byteshell");
        }
      } else if (strcmp(name, "TEXT_FONT") == 0) {
        free(*text_font);
        *text_font = malloc(strlen(value) + 1);
        strcpy(*text_font, value);
      } else {
        fprintf(stderr, "Unknown directive %s\n",
                name);  // Otherwise, print an error message
      }
      free(name);  // Free the memory allocated by sscanf for name
    } else {
      fprintf(stderr,
              "Invalid format in config file\n");  // Print an error message if
                                                   // sscanf fails
    }
  }

  fclose(file);  // Close the file stream
  return 1;      // Return a success code
}

void launch_shell() {
#ifndef BUF_SIZE
#define BUF_SIZE 64
#endif
  char *start_path = malloc(BUF_SIZE);
  char *path_font = "\x1b[36m\x1b[1m";
  char *text_font = "\x1b[0m";

  getcwd(start_path, BUF_SIZE);
  if (start_path == NULL) {
    perror("_getcwd");
    exit(EXIT_FAILURE);
  }
  char *home_path = getenv("HOME");
  if (home_path) {
    free(start_path);
    start_path = malloc(strlen(home_path) + 1);
    strcpy(start_path, home_path);
    if (chdir(home_path) != 0) {
      perror("byteshell");
    }
    setup_config(".byte_config", &path_font, &text_font);
  }
  // char **s = environ;
  // for (; *s; s++) {
  //   printf("%s\n", *s);
  // }
  while (true) {
    char *curr_path = malloc(BUF_SIZE);

    getcwd(curr_path, BUF_SIZE);
    if (curr_path == NULL) {
      perror("_getcwd");
      exit(EXIT_FAILURE);
    }

    printf("%s%s: %s$ ", path_font, curr_path, text_font);

    char *line = shell_read_line();
    char *history_line = malloc(strlen(line) + 1);

    strcpy(history_line, line);
    strtok(history_line, "\n");

    struct ListNode *tokens = get_tokens(line, " \t\r\n");

    if (tokens != NULL) {
      run_shell_cmd(tokens, start_path);
      prepend_history(history_line, start_path);
    }

    free_list(&tokens);
    free(line);
    free(history_line);
    free(curr_path);
  }

  free(start_path);
}