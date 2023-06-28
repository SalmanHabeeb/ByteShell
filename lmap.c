#include "lmap.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MapNode* create_map_node(char* key, char* value) {
  struct MapNode* node =
      malloc(sizeof(struct MapNode));  // Allocate memory for the node
  if (node == NULL) {                  // Check if allocation failed
    perror("malloc");
    return NULL;
  }
  node->key = strdup(key);      // Copy the key string
  node->value = strdup(value);  // Copy the value string
  node->next = NULL;            // Set the next pointer to NULL
  return node;                  // Return the node
}

struct MapNode* append_map(struct MapNode* head, char* key, char* values) {
  struct MapNode* newNode = create_map_node(key, values);
  if (newNode == NULL) {
    return head;
  }

  if (head == NULL) {
    return newNode;
  }

  struct MapNode* current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = newNode;
  return head;
}

struct MapNode* get_map_node_by_key(struct MapNode* head, char* key) {
  struct MapNode* current = head;
  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

bool delete_map_node_by_key(struct MapNode* head, char* key) {
  if (head == NULL) {
    return false;
  }

  struct MapNode* current = head;
  struct MapNode* previous = NULL;

  // If the node to be deleted is the head node
  if (strcmp(current->key, key) == 0) {
    head = current->next;
    free(current->key);
    free(current->value);
    free(current);
    return true;
  }

  // Traverse the list to find the node to be deleted
  while (current != NULL && strcmp(current->key, key) != 0) {
    previous = current;
    current = current->next;
  }

  // If the node was found, delete it
  if (current != NULL) {
    previous->next = current->next;
    free(current->key);
    free(current->value);
    free(current);
    return true;
  }

  return false;
}

void display_map(struct MapNode* head) {
  struct MapNode* current = head;
  while (current != NULL) {
    printf("Key: %s, Values: %s\n", current->key, current->value);
    current = current->next;
  }
}

void free_map(struct MapNode* head) {
  struct MapNode* current = head;
  while (current != NULL) {
    struct MapNode* temp = current;
    current = current->next;
    free(temp->key);
    free(temp->value);
    free(temp);
  }
}
