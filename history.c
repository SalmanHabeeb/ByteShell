#include "history.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"

void show_history(char* path) {
  struct ListNode* history = get_history(path);
  //   printf("%s", history->data);
  history = reverse_list(history);
  display_list(history);
  free_list(&history);
}

struct ListNode* get_history(char* path) {
  char* filename = malloc(strlen(path) + strlen("/history.dat") + 1);
  if (filename == NULL) {
    return create_node("");
  }

  strcpy(filename, path);
  strcat(filename, "/history.dat");
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    return create_node("");
  }

  char buffer[256];
  struct ListNode* head = NULL;
  struct ListNode* tail = NULL;

  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    buffer[strcspn(buffer, "\n")] = '\0';
    struct ListNode* newNode = create_node(buffer);
    if (newNode == NULL) {
      fclose(file);
      free_list(&head);
      return NULL;
    }

    if (head == NULL) {
      head = newNode;
      tail = newNode;
    } else {
      tail->next = newNode;
      tail = tail->next;
    }
  }

  fclose(file);
  return head;
}

void write_history(struct ListNode* node, char* path) {
  char* filename = malloc(strlen(path) + strlen("/history.dat") + 1);
  if (filename == NULL) {
    return;
  }

  strcpy(filename, path);
  strcat(filename, "/history.dat");

  FILE* file = fopen(filename, "w");
  if (file == NULL) {
    fprintf(stderr, "Failed to open history file");
    return;
  }

  while (node != NULL) {
    fprintf(file, "%s\n", node->data);
    node = node->next;
  }
  fclose(file);
}

void prepend_history(char* data, char* path) {
  struct ListNode* history = get_history(path);
  history = prepend_list(history, data);
  write_history(history, path);
  free_list(&history);
}