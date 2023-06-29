#include "lmap.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This function creates a new MapNode with the given key and value
// It returns a pointer to the new node, or NULL if memory allocation fails
struct MapNode *create_map_node(char *key, char *value) {
  // Allocate memory for the new node
  struct MapNode *new_node = malloc(sizeof(struct MapNode));
  if (new_node == NULL) {
    // Handle memory allocation error
    return NULL;
  }

  // Allocate memory and copy the key and value strings
  new_node->key = malloc(strlen(key) + 1);
  new_node->value = malloc(strlen(value) + 1);
  if (new_node->key == NULL || new_node->value == NULL) {
    // Handle memory allocation error
    free(new_node);
    return NULL;
  }
  strcpy(new_node->key, key);
  strcpy(new_node->value, value);

  // Set the next pointer of the new node to NULL
  new_node->next = NULL;

  // Return the new node
  return new_node;
}

// This function appends a MapNode to the end of a linked list
// It takes a pointer to the head of the list and a pointer to the node to be
// appended as parameters It returns nothing
struct MapNode *append_map_node(struct MapNode *head, struct MapNode *node) {
  // If the list is empty, set the head to the node
  if (head == NULL) {
    head = node;
    return head;
  }

  // Create a pointer to traverse the list
  struct MapNode *current = head;

  // Find the last node of the list
  while (current->next != NULL) {
    current = current->next;
  }

  // Set the next pointer of the last node to the node to be appended
  current->next = node;
  return head;
}

// This function deletes a MapNode by its key from a linked list
// It takes a pointer to the head of the list and a key string as parameters
// It returns true if the deletion is successful, or false if the key is not
// found or memory deallocation fails
struct MapNode *delete_map_node_by_key(struct MapNode *head, char *key) {
  // If the list is empty, return false
  if (head == NULL) {
    return NULL;
  }

  // Create a pointer to store the previous node of the current node
  struct MapNode *prev = NULL;

  // Create a pointer to traverse the list
  struct MapNode *current = head;

  // Find the node with the matching key
  while (current != NULL && strcmp(current->key, key) != 0) {
    prev = current;
    current = current->next;
  }

  // If the key is not found, return false
  if (current == NULL) {
    return head;
  }

  // If the node to be deleted is the head node, set the head to the next node
  if (prev == NULL) {
    head = current->next;
  }
  // Otherwise, set the next pointer of the previous node to the next node of
  // the current node
  else {
    prev->next = current->next;
  }

  // Free the memory allocated for the current node and its key and value
  // strings
  free(current->key);
  free(current->value);

  free(current);

  // Return true to indicate successful deletion
  return head;
}

// This function returns a pointer to a MapNode by its key from a linked list
// It takes a pointer to the head of the list and a key string as parameters
// It returns a pointer to the matching node, or NULL if not found
struct MapNode *get_map_node_by_key(struct MapNode *head, char *key) {
  // Create a pointer to traverse the list
  struct MapNode *current = head;

  // Find the node with the matching key
  while (current != NULL && strcmp(current->key, key) != 0) {
    current = current->next;
  }

  // Return the matching node or NULL
  return current;
}

// This function frees the memory allocated for a linked list of MapNodes
// It takes a pointer to the head of the list as a parameter
// It returns nothing
void free_map(struct MapNode *head) {
  // Create a pointer to store the current node
  struct MapNode *current = head;

  // Create a pointer to store the next node
  struct MapNode *next = NULL;

  // Traverse the list until the end is reached
  while (current != NULL) {
    // Save the next node
    next = current->next;

    // Free the memory allocated for the current node and its key and value
    // strings
    free(current->key);
    free(current->value);
    free(current);

    // Move to the next node
    current = next;
  }

  // Set the head to NULL
  head = NULL;
}
