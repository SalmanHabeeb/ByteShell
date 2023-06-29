#include <stdbool.h>

#ifndef LLIST_H_
#define LLIST_H_
#define MAX_LLIST_LENGTH 300
struct MapNode {
  char* key;
  char* value;
  struct MapNode* next;
};
struct MapNode* create_map_node(char* key, char* values);
struct MapNode* append_map_node(struct MapNode* head, struct MapNode* node);
struct MapNode* get_map_node_by_key(struct MapNode* head, char* key);
struct MapNode* delete_map_node_by_key(struct MapNode* head, char* key);
// void display_map(struct MapNode* head);
void free_map(struct MapNode* head);
#endif