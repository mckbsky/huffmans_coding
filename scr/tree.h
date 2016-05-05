#ifndef TREE_H
#define TREE_H
#include <stdio.h>

struct treeNode {
  int freq;
  char c;
  struct treeNode *left, *right;
};

struct list_node {
  unsigned int code:2;
  struct list_node *prev, *next;
};

struct list_pointers {
    struct list_node *head, *tail;
};

struct treeNode *root = NULL;
struct treeNode histogram[256];

struct list_node* createList(void);

void insertListNode(struct list_pointers *list);

void saveCode(struct list_pointers *list, char c);

void deleteListNode(struct list_pointers *list);

void generateTree(struct treeNode *histogram, int n, struct treeNode *root);

void createCodes(struct treeNode *root);

void encode(int (*codes)[256], char *inputFile, char *outputFile);

void writeToFile(char *inputFile, char *outputFile);

void decode(struct treeNode *root, char *inputFile, char *outputFile);

void removeTree(struct treeNode *root);

void prepareHistogram (struct treeNode *histogram);

void createHistogram(char *inputFile, struct treeNode *histogram);

void quickSort(struct treeNode *histogram, int begin, int end, int flag);

#endif //tree.h
