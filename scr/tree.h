#ifndef TREE_H
#define TREE_H
#include <stdio.h>

//drzewo poszukiwan binarnych: Binary Search Tree
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


/*
 * TODO: Mariusz - wypełnienie tablicy struktur kolejnymi literami i ustawienie
 * int occ na 0
 * NOTE: uwzględniać wielkośc liter?
 */

void prepareHistogram(bsTree *histogram);

/*
 * TODO: Mariusz - funkcja otwiera plik tekstowy o nazwie podanej jako argument
 * wywołania i tworzy na jego podstawie histogram występowania poszczególnych
 * liter
 */
void createHistogram(char* filename, bsTree *histogram);

/*
 * TODO: sortowanie względem ilości wystąpień danej litery
 * NOTE: początkowo może to być jakieś proste sortowanie, docelowo qsort
 */

void quickSort(bsTree *histogram);

#endif //tree.h
