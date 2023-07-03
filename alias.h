#include "lmap.h"

#ifndef ALIAS_H_
#define ALIAS_H_

struct MapNode* get_aliases(char* path);
struct MapNode* get_alias(char* key, char* path);
void show_aliases(char* start_path);
void write_aliases(struct MapNode* aliases, char* start_path);
void create_alias(char* key, char* value, char* start_path);
void remove_alias(char* key, char* start_path);
void remove_all_aliases(char* start_path);
#endif