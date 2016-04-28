#ifndef TREE_H
#define TREE_H
#include <stdio.h>

//binarne drzewo poszukiwan: Binary Search Tree
struct bsTreeNode {
  int freq;
  char c;
  struct bsTreeNode *left, *right;
};

struct list_node {
  unsigned int code:2;
  struct list_node *prev, *next;
};

struct list_pointers {
    struct list_node *head, *tail;
};

typedef struct list_node list;
typedef struct bsTreeNode bsTree;

bsTree *root = NULL;
bsTree histogram[256];

int **codes[256][];

list* create_list(void);
void insert_list_node(list *head);
void saveCode(list *head, char c);
void delete_list_node(list *head);




void generateBSTree(bsTree *histogram, int n, bsTree *root);

void encode(bsTree *root);

void writeToFile(char *inputFile, char *outputFile);

/*
 * TODO: Maciek, Mariusz: funkcja dekodująca z pliku zakodowany ciąg zer i
 * jedynek
 */

void decode(bsTree *root, char *inputFile);

void removeTree(bsTree *root);

void prepareHistogram(bsTree *histogram);


void createHistogram(char* inputFile, bsTree *histogram);


void quickSort(bsTree *histogram, int begin, int end, int flag);

#endif //tree.h
