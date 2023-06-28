#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for the map node
struct MapNode {
  char* key;
  char* value;
  struct MapNode* next;
};

// Write a function to create a new map node with given key and value
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

// Write a function to append a map node to the end of a linked list
void append_map_node(struct MapNode** head, struct MapNode* node) {
  if (*head == NULL) {  // If the list is empty, set the head to the node
    *head = node;
  } else {  // Otherwise, traverse the list until the end and insert the node
            // there
    struct MapNode* current = *head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = node;
  }
}

// Write a function to print a map node
void print_map_node(struct MapNode* node) {
  printf("Key: %s, Value: %s\n", node->key, node->value);
}

// Write a function to print a linked list of map nodes
void print_map_list(struct MapNode* head) {
  struct MapNode* current = head;
  while (current != NULL) {
    print_map_node(current);
    current = current->next;
  }
}

// Write a function to free a map node
void free_map_node(struct MapNode* node) {
  free(node->key);    // Free the key string
  free(node->value);  // Free the value string
  free(node);         // Free the node itself
}

// Write a function to free a linked list of map nodes
void free_map_list(struct MapNode* head) {
  struct MapNode* current = head;
  struct MapNode* next;
  while (current != NULL) {
    next = current->next;    // Save the next pointer
    free_map_node(current);  // Free the current node
    current = next;          // Move to the next node
  }
}

// Write a function to write a linked list of map nodes to a binary file
int write_map_list(const char* filename, struct MapNode* head) {
  FILE* file = fopen(filename, "wb");  // Open the file in write binary mode
  if (file == NULL) {                  // Check if opening failed
    perror("fopen");
    return -1;
  }
  struct MapNode* current = head;
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
      perror("fwrite");
      fclose(file);
      return -1;
    }

    current = current->next;  // Move to the next node
  }
  fclose(file);  // Close the file
  return 0;      // Return success
}

// Write a function to read a linked list of map nodes from a binary file
struct MapNode* read_map_list(const char* filename) {
  FILE* file = fopen(filename, "rb");  // Open the file in read binary mode
  if (file == NULL) {                  // Check if opening failed
    perror("byteshell");
    return NULL;
  }
  struct MapNode* head = NULL;
  size_t key_len;
  size_t value_len;

  // Read the key length from the file until the end of the file is reached
  while (fread(&key_len, sizeof(size_t), 1, file) == 1) {
    char* key = malloc(key_len + 1);
    if (key == NULL) {
      perror("malloc");
      fclose(file);
      free_map_list(head);
      return NULL;
    }

    // Read the key string from the file
    if (fread(key, sizeof(char), key_len, file) != key_len) {
      perror("fread");
      fclose(file);
      free(key);
      free_map_list(head);
      return NULL;
    }
    key[key_len] = '\0';  // Add a null terminator to the key string

    // Read the value length from the file
    if (fread(&value_len, sizeof(size_t), 1, file) != 1) {
      perror("fread");
      fclose(file);
      free(key);
      free_map_list(head);
      return NULL;
    }

    char* value =
        malloc(value_len + 1);  // Allocate memory for the value string
    if (value == NULL) {        // Check if allocation failed
      perror("malloc");
      fclose(file);
      free(key);
      free_map_list(head);
      return NULL;
    }

    // Read the value string from the file
    if (fread(value, sizeof(char), value_len, file) != value_len) {
      perror("fread");
      fclose(file);
      free(key);
      free(value);
      free_map_list(head);
      return NULL;
    }
    value[value_len] = '\0';  // Add a null terminator to the value string

    // Create a new map node with the key and value
    struct MapNode* node = create_map_node(key, value);

    // Append the node to the list
    append_map_node(&head, node);

    // Free the key and value strings as they are copied by create_map_node
    free(key);
    free(value);
  }
  fclose(file);  // Close the file
  return head;   // Return the list
}

// Write a main function to test the code
int main() {
  // Create a sample linked list of map nodes
  struct MapNode* list = NULL;
  append_map_node(&list, create_map_node("apple", "red"));
  append_map_node(&list, create_map_node("banana", "yellow"));
  append_map_node(&list, create_map_node("orange", "orange"));

  // Print the list
  printf("Original list:\n");
  print_map_list(list);

  // Write the list to a binary file
  const char* filename = "map.bin";
  if (write_map_list(filename, list) == -1) {
    fprintf(stderr, "Failed to write to %s\n", filename);
    free_map_list(list);
    return -1;
  }

  // Free the list
  free_map_list(list);

  // Read the list from the binary file
  list = read_map_list(filename);
  if (list == NULL) {
    fprintf(stderr, "Failed to read from %s\n", filename);
    return -1;
  }

  // Print the list
  printf("Read list:\n");
  print_map_list(list);

  // Free the list
  free_map_list(list);

  return 0;
}
