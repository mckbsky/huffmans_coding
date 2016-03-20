#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include "histogram.h"

//drzewo poszukiwan binarnych: Binary Search Tree
struct bsTreeTemplate {
  int id;
  struct bsTree *left, *right;
};

typedef struct bsTreeTemplate bsTree;
bsTree *tree = NULL;

/*
 * TODO: Maciek - generowanie drzewa poszukiwań binarnych na podstawie
 * posortowanego histogramu
 */

void generateBSTree(histogram *hArray, bsTree *tree);

/*
 * TODO: Maciek - funckja zapisuje zakodowany ciąg zer i jedynek do pliku
 */

void encode(bsTree *tree, char *outputFile);

/*
 * TODO: Maciek, Mariusz: funkcja dekodująca z pliku zakodowany ciąg zer i
 * jedynek
 */

void decode(bsTree *tree, char* inputFile);


#endif //tree.h
