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
  struct list_node *next;
};

typedef struct list_node list;
typedef struct bsTreeNode bsTree;

bsTree *root = NULL;
bsTree histogram[25];

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


void prepareHistogram(bsTree *histogram);


void createHistogram(char* inputFile, bsTree *histogram);

/*
 * TODO: sortowanie względem ilości wystąpień danej litery
 * NOTE: początkowo może to być jakieś proste sortowanie, docelowo qsort
 */

void quickSort(bsTree *histogram);

#endif //tree.h
