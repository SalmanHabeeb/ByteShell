#include "alias.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lmap/lmap.h"

struct MapNode* get_aliases(char* path) {
  char* filename = malloc(strlen(path) + strlen("/.byte_aliases") + 1);
  if (filename == NULL) {
    return NULL;
  }

  strcpy(filename, path);
  strcat(filename, "/.byte_aliases");

  FILE* file = fopen(filename, "rb");  // Open the file in binary read mode
  free(filename);

  if (file == NULL) {
    return NULL;
  }

  struct MapNode* head = NULL;
  size_t key_len;
  size_t value_len;

  // Read the key length from the file until the end of the file is reached
  while (fread(&key_len, sizeof(size_t), 1, file) == 1) {
    char* key = malloc(key_len + 1);
    if (key == NULL) {
      perror("byteshell");
      fclose(file);
      free_map(&head);
      return NULL;
    }

    // Read the key string from the file
    if (fread(key, sizeof(char), key_len, file) != key_len) {
      perror("byteshell");
      fclose(file);
      free(key);
      free_map(&head);
      return NULL;
    }
    key[key_len] = '\0';  // Add a null terminator to the key string

    // Read the value length from the file
    if (fread(&value_len, sizeof(size_t), 1, file) != 1) {
      perror("byteshell");
      fclose(file);
      free(key);
      free_map(&head);
      return NULL;
    }

    char* value =
        malloc(value_len + 1);  // Allocate memory for the value string
    if (value == NULL) {        // Check if allocation failed
      perror("byteshell");
      fclose(file);
      free(key);
      free_map(&head);
      return NULL;
    }

    // Read the value string from the file
    if (fread(value, sizeof(char), value_len, file) != value_len) {
      perror("byteshell");
      fclose(file);
      free(key);
      free(value);
      free_map(&head);
      return NULL;
    }
    value[value_len] = '\0';  // Add a null terminator to the value string

    // Create a new map node with the key and value
    // struct MapNode* node = create_map_node(key, value);

    // Append the node to the list
    struct MapNode* node = create_map_node(key, value);
    head = append_map_node(head, node);

    // Free the key and value strings as they are copied by create_map_node
    free(key);
    free(value);
  }

  fclose(file);
  return head;
}

struct MapNode* get_alias(char* key, char* start_path) {
  struct MapNode* aliases = get_aliases(start_path);
  struct MapNode* node = get_map_node_by_key(aliases, key);
  // free_map(&aliases);
  return node;
}

void show_aliases(char* start_path) {
  struct MapNode* aliases = get_aliases(start_path);
  if (aliases == NULL) {
    fprintf(stderr, "No aliases\n");
    return;
  }
  struct MapNode* current = aliases;

  while (current != NULL) {
    fprintf(stderr, "alias %s='%s'\n", current->key, current->value);
    current = current->next;
  }
  free_map(&aliases);
}

void write_aliases(struct MapNode* head, char* path) {
  char* filename = malloc(strlen(path) + strlen("/.byte_aliases") + 1);
  if (filename == NULL) {
    return;
  }

  strcpy(filename, path);
  strcat(filename, "/.byte_aliases");

  FILE* file = fopen(filename, "wb");  // Open the file in binary write mode
  if (file == NULL) {
    fprintf(stderr, "Failed to open aliases file");
    free(filename);
    return;
  }

  struct MapNode* current = head;
  // fprintf(stderr, "%s", current->key);  // debug
  while (current != NULL) {
    size_t key_len = strlen(current->key);  // Get the length of the key string
    size_t value_len =
        strlen(current->value);  // Get the length of the value string

    // Write the key length, key string, value length and value string to the
    // file
    if (fwrite(&key_len, sizeof(size_t), 1, file) != 1 ||
        fwrite(current->key, sizeof(char), key_len, file) != key_len ||
        fwrite(&value_len, sizeof(size_t), 1, file) != 1 ||
        fwrite(current->value, sizeof(char), value_len, file) != value_len) {
      perror("byteshell");
      fclose(file);
      return;
    }

    current = current->next;  // Move to the next node
  }

  fclose(file);
  free(filename);
}

void create_alias(char* key, char* value, char* start_path) {
  struct MapNode* aliases = get_aliases(start_path);
  struct MapNode* new_alias = create_map_node(key, value);

  aliases = append_map_node(aliases, new_alias);
  // fprintf(stderr, "%s, %s", aliases->key, aliases->value);
  write_aliases(aliases, start_path);
  free_map(&aliases);
}

void remove_alias(char* key, char* start_path) {
  struct MapNode* aliases = get_aliases(start_path);
  aliases = delete_map_node_by_key(aliases, key);
  write_aliases(aliases, start_path);
  free_map(&aliases);
}

void remove_all_aliases(char* start_path) {
  write_aliases(NULL, start_path);  // Overwrite existing aliases
}