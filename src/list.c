#include "../headers/list.h"
#include <stdio.h>
#include <stdlib.h>

void createList(struct listPointers *list) {
  struct listNode *new_node = (struct listNode *)malloc(sizeof(struct listNode));
  if (new_node != NULL) {
    new_node->next = new_node->prev = NULL;
    list->head = list->tail = new_node;
  }
}

void insertListNode(struct listPointers *list) {
  if(list) {
    struct listNode *new_node = (struct listNode*)malloc(sizeof(struct listNode));
    if(new_node) {
      new_node->prev = NULL;
      new_node->next = list->head;
      list->head->prev = new_node;
      list->head = new_node;
    }
  }
  else {
    fprintf(stderr, "Error: Empty list, can't add new element\n");
  }
}

void deleteListNode(struct listPointers **list) {
  if((*list)->head == NULL) {
    fprintf(stderr, "Can't delete node from empty list\n");
    return;
  }
  struct listNode* deleted_node = (*list)->head;
  (*list)->head = deleted_node->next;
  free(deleted_node);
}