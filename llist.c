#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"llist.h"

struct ListNode* create_node(const char* data) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (newNode == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    newNode->data = strdup(data);
    newNode->next = NULL;
    return newNode;
}

struct ListNode* prepend_list(struct ListNode* head, const char* data) {
    struct ListNode* newNode = create_node(data);
    if (newNode == NULL) {
        return NULL;
    }

    newNode->next = head;
    head = newNode;
    struct ListNode* curr = head;
    int counter = 0;
    while (curr) {
        if (counter >= MAX_LLIST_LENGTH) {
            free_list(curr);
            break;
        }
        curr = curr->next;
        counter++;
    }
    return head;
}

struct ListNode* reverse_list(struct ListNode* head) {
    struct ListNode *prev = NULL;
    struct ListNode *curr = head;
    while(curr) {
        struct ListNode *temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    return prev;
}


void display_list(struct ListNode* head) {
    struct ListNode* current = head;
    if (current == NULL) {
        return;
    }
    while (current != NULL) {
        printf("%s \n", current->data);
        current = current->next;
    }
}

void free_list(struct ListNode* head) {
    struct ListNode* current = head;
    while (current != NULL) {
        struct ListNode* temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
}