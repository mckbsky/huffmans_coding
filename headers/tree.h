#ifndef TREE_H
#define TREE_H
#include <stdio.h>

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

void createList(struct list_pointers *list);

void insertListNode(struct list_pointers *list);

void saveCode(struct list_pointers *list, char c);

void deleteListNode(struct list_pointers **list);

struct treeNode* generateTree(struct treeNode *root, struct treeNode *histogram, int n);

void createCodes(struct list_pointers *list, struct treeNode *root);

void encode(char *inputFile, char *outputFile);

void writeToFile(char *inputFile, char *outputFile);

void decode(struct treeNode *root, char *inputFile, char *outputFile);

void removeTree(struct treeNode *root);

void prepareHistogram (struct treeNode *histogram);

void createHistogram(char *inputFile, struct treeNode *histogram);

void quickSortChar(struct treeNode *histogram, int begin, int end);

void quickSortFreq(struct treeNode *histogram, int begin, int end);


#endif //tree.h
