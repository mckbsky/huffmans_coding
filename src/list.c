#include "../headers/list.h"
#include <stdio.h>
#include <stdlib.h>

void createList(struct listPointers *list) {
  struct listNode *newNode = (struct listNode *)malloc(sizeof(struct listNode));
  if (newNode != NULL) {
    newNode->next = newNode->prev = NULL;
    list->head = list->tail = newNode;
  }
}

void insertListNode(struct listPointers *list) {
  if(list) {
    struct listNode *newNode = (struct listNode*)malloc(sizeof(struct listNode));
    if(newNode) {
      newNode->prev = NULL;
      newNode->next = list->head;
      list->head->prev = newNode;
      list->head = newNode;
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
  struct listNode* deletedNode = (*list)->head;
  (*list)->head = deletedNode->next;
  free(deletedNode);
}