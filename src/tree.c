#include "../headers/tree.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct treeNode* addLeaf(struct treeNode *histogram, int index) {
  struct treeNode *node = (struct treeNode *)calloc(1, sizeof(struct treeNode));
  node->c = histogram[index].c;
  return node;
}

struct treeNode* addTwoLeaves(struct treeNode *histogram, int index) {
  struct treeNode *node = (struct treeNode *)calloc(1, sizeof(struct treeNode));
  node->left = (struct treeNode *)calloc(1, sizeof(struct treeNode));
  node->left->c = histogram[index - 1].c;
  node->right = (struct treeNode *)calloc(1, sizeof(struct treeNode));
  node->right->c = histogram[index].c;
  return node;
}

struct treeNode* addLeafToLeftBranch(struct treeNode *histogram,
                                     struct treeNode *root, int index) {
  struct treeNode *node = (struct treeNode *)calloc(1, sizeof(struct treeNode));
  node->left = (struct treeNode *)calloc(1, sizeof(struct treeNode));
  node->left->c = histogram[index].c;
  node->right = root;
  return node;
}

struct treeNode* addTwoLeavesAndCreateNewRoot(struct treeNode *histogram,
                                              struct treeNode *root,
                                              int index) {
  struct treeNode *node = (struct treeNode *)calloc(1, sizeof(struct treeNode));
  node->left = (struct treeNode *)calloc(1, sizeof(struct treeNode));
  node->left->c = histogram[index - 1].c;
  node->right = (struct treeNode *)calloc(1, sizeof(struct treeNode));
  node->right->c = histogram[index].c;

  struct treeNode *newRoot = (struct treeNode *)calloc(1, sizeof(struct treeNode));
  newRoot->left = node;
  newRoot->right = root;
  return newRoot;
}

struct treeNode* generateTree(struct treeNode *root, struct treeNode *histogram) {
  int index = findHistogramSize(histogram);

  while(index >= 0) {
    if(NULL != root) {
      if(index == 0) {
        root = addLeafToLeftBranch(histogram, root, index);
      }
      else {
        root = addTwoLeavesAndCreateNewRoot(histogram, root, index);
      }
    }
    else {
      if(index == 0) {
        root = addLeaf(histogram, index);
      }
      else {
        root = addTwoLeaves(histogram, index);
      }
    }
    index -= NUMBER_OF_NODES;
  }
  return root;
}

void createCodes(struct treeNode *root, struct listPointers *list) {
  if(isSingleLeafTree(root, list)) {
    insertListNode(list);
    list->head->code = CODE_LEFT;
  }

  if(isLeaf(root)) {
    saveCode(list, root->c);
    deleteListNode(&list);
    return;
  }

  insertListNode(list);
  list->head->code = CODE_RIGHT;
  createCodes(root->right, list);
  insertListNode(list);
  list->head->code = CODE_LEFT;
  createCodes(root->left, list);
  deleteListNode(&list);
}

bool isSingleLeafTree(struct treeNode *root, struct listPointers *list) {
  return root->left == NULL && root->right == NULL && list->head == list->tail;
}

bool isLeaf(struct treeNode *root) {
  return root->c != 0;
}

void saveCode(struct listPointers *list, unsigned char c) {
  struct listNode *tmp = list->tail->prev;
  unsigned int i;
  size_t allocatedChunks = 0;

  for(i = 0; tmp != NULL; i++) {
    if(i + 2 >= allocatedChunks) {
      allocatedChunks += 10;
      codes[c] = (char *)realloc(codes[c], (allocatedChunks) * sizeof(char));
    }
    codes[c][i] = tmp->code;
    codes[c][i + 1] = '\0';
    tmp = tmp->prev;
  }
}

void removeTree(struct treeNode *root) {
  if(root->left == NULL && root->right == NULL) {
    free(root);
    root = NULL;
    return;
  }
  removeTree(root->right);
  if(root->left != NULL) {
    removeTree(root->left);
  }
  free(root);
}
