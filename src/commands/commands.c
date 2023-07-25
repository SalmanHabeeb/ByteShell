#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../alias/alias.h"
#include "../history/history.h"
#include "../llist/llist.h"
#include "../parse/parse.h"
#include "../ulimit/ulimit.h"

void exit_command(char **args, char *start_path) { exit(0); }

void cd_command(char **args, char *start_path) {
  if (args[1] == NULL) {
    fprintf(stderr, "byteshell: cd: missing argument\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("byteshell");
    }
  }
}

void help_command(char **args, char *start_path) {
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

void show_license_command(char **args, char *start_path) {
  if (args[1] == NULL ||
      (strcmp("--l", args[1]) != 0 && strcmp("--mini", args[1]) != 0)) {
    fprintf(stderr,
            "show command.\nUse show with following parameters:\n\
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

// Function to count the number of tokens in an array
// int count_tokens(char **tokens) {
//   int count = 0;
//   while (tokens[count] != NULL) {
//     count++;
//   }
//   return count;
// }

// // Function to concatenate tokens into a single string
// char *concat_tokens(char **tokens, int start_index, int end_index) {
//   int total_length = 0;
//   for (int i = start_index; i <= end_index; i++) {
//     total_length += strlen(tokens[i]);
//   }

//   char *result = malloc(total_length + 1);  // +1 for the null terminator
//   if (result == NULL) {
//     fprintf(stderr, "Failed to allocate memory.\n");
//     exit(1);
//   }

//   result[0] = '\0';  // Initialize the result string as an empty string

//   for (int i = start_index; i <= end_index; i++) {
//     strcat(result, tokens[i]);
//   }

//   return result;
// }

void alias_command(char **args, char *start_path) {
  if (args[1] != NULL) {
    if (strcmp(args[1], "-p") == 0) {
      show_aliases(start_path);
      return;
    } else {
      char *alias_arg = concat_tokens(args + 1, " ");
      struct ListNode *tokens = get_tokens(alias_arg, "='\"");
      free(alias_arg);
      alias_arg = NULL;
      if (tokens != NULL && tokens->next != NULL) {
        create_alias(tokens->data, tokens->next->data, start_path);
      } else if (tokens != NULL) {
        fprintf(stderr, "byteshell: Invalid arguments\n");
      }
      free(tokens);
      tokens = NULL;
    }
  } else {
    fprintf(stderr,
            "alias command.\nUse alias with following parameters:\n\
                -p - show all aliases\n");
  }
}

void unalias_command(char **args, char *start_path) {
  if (args[1] != NULL) {
    if (strcmp(args[1], "-a") == 0) {
      remove_all_aliases(start_path);
    } else {
      remove_alias(args[1], start_path);
    }
  }
}

void ulimit_command(char **args, char *start_path) {
  if (args[1] == NULL) {
  } else if (args[1] != NULL) {
    if (strcmp(args[1], "-a") == 0) {
      show_all_limits();
    } else {
      if (args[2] != NULL && strlen(args[1]) >= 2) {
        long num;
        sscanf(args[2], "%ld", &num);
        set_limit_option(args[1][1], num);
      } else if (strlen(args[1]) >= 2) {
        show_limit(args[1][1]);
      }
    }
  }
}