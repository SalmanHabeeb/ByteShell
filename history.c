#include<stdio.h>
#include<stdlib.h>

#include"history.h"
#include"llist.h"
#include<string.h>


void show_history(struct ListNode* history) {
    display_list(history);
}

struct ListNode* get_history() {
    FILE* file = fopen("history.dat", "r");
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
            free_list(head);
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
    char *filename = malloc(strlen(path) + strlen("/history.dat") + 1);
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

struct ListNode* prepend_history(struct ListNode* history, char* data, char* path) {
    history = prepend_list(history, data);
    write_history(history, path);
    return history;
}