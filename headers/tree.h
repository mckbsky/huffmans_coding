#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct treeNode {
  int freq;
  char c;
  struct treeNode *left, *right;
};

struct list_node {
  char code;
  struct list_node *prev, *next;
};

struct list_pointers {
    struct list_node *head, *tail;
};

extern char **codes;

bool createHistogram(char *inputFile, struct treeNode *histogram);

void quickSort(struct treeNode *histogram, int begin, int end, int type);

int *getHistogram(struct treeNode *histogram, int i, int type);

struct treeNode* generateTree(struct treeNode *root, struct treeNode *histogram);

void createCodes(struct list_pointers *list, struct treeNode *root);

void saveCode(struct list_pointers *list, char c);

void createList(struct list_pointers *list);

void insertListNode(struct list_pointers *list);

void deleteListNode(struct list_pointers **list);

void encode(char *inputFile, char *outputFile);

void decode(struct treeNode *root, char *inputFile, char *outputFile);

void removeTree(struct treeNode *root);

#endif //tree.h
