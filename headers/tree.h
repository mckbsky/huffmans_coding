#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*!
 * \struct treeNode
 * \brief Struktura węzła drzewa
 *
 * Strukura zawiera pola c dla kodowanego znaku, freq dla ilości jej wystąpień,
 * zeroes, wykorzystywaną do zapisu ilości zer w kodach znaków i pola wskażnikowe
 * left i right dla potomstwa danego węzła.
 */

struct treeNode {
  unsigned char c;
  int freq;
  int zeroes;
  struct treeNode *left, *right;
};

/*!
 * \struct list_node
 * \brief Typ bazowy listy dwukierunkowej
 *
 * Wykorzystywana jako bufer do zapisu kodów przy przechodzeniu przez drzewo.
 * Zawiera pole code przechowujące znak '0' lub '1' w zależności od kierunku
 * odwiedzania węzłów
 */

struct list_node {
  char code;
  struct list_node *prev, *next;
};

/*!
 * \struct list_pointers
 * \brief Struktura wskaźników do listy
 *
 * Tworzymy listę dwustronną, abt ułatwić odczyt kodów
 */

struct list_pointers {
  struct list_node *head, *tail;
};

/*!
 * \var char **codes
 * \brief Kody każdego ze znaków
 *
 * Tablica wskaźników na tablice zawierające kody dla znaków ascii
 * występujących w histogramie
 */

extern char **codes;

/*!
 * \fn bool createHistogram(char *inputFile, struct treeNode *histogram);
 * \brief Funkcja tworząca histogram
 *
 * Funkcja przyjmuje dwa parametry: char *inputFile - nazwa pliku wejściowego,
 * struct treeNode *histogram - tablica
 */

bool createHistogram(char *inputFile, struct treeNode *histogram);

/*!
 * \fn
 * \brief
 *
 * Maciek
 */

void quickSort(struct treeNode *histogram, int begin, int end, int type);

/*!
 * \fn
 * \brief
 *
 * Mariusz
 */

long *getHistogram(struct treeNode *histogram, int i, int type);

/*!
 * \fn
 * \brief
 *
 * Maciek
 */

struct treeNode* generateTree(struct treeNode *root, struct treeNode *histogram);

/*!
 * \fn
 * \brief
 *
 * Mariusz
 */

void createCodes(struct list_pointers *list, struct treeNode *root);

/*!
 * \fn
 * \brief
 *
 * Maciek
 */

void saveCode(struct list_pointers *list, char c);

/*!
 * \fn
 * \brief
 *
 * Mariusz
 */

void createList(struct list_pointers *list);

/*!
 * \fn
 * \brief
 *
 * Maciek
 */

void insertListNode(struct list_pointers *list);

/*!
 * \fn
 * \brief
 *
 * Mariusz
 */

void deleteListNode(struct list_pointers **list);

/*!
 * \fn
 * \brief
 *
 * Maciek
 */

double encode(char *input, char *outputFile, struct treeNode *histogram);

/*!
 * \fn
 * \brief
 *
 * Mariusz
 */

unsigned char binToAscii(unsigned char *array, struct treeNode *histogram);

/*!
 * \fn
 * \brief
 *
 * Maciek
 */

void generateKey(struct treeNode *histogram);

/*!
 * \fn
 * \brief
 *
 * Mariusz
 */

void keyToHistogram(char *key, struct treeNode *histogram);

/*!
 * \fn
 * \brief
 *
 * Maciek
 */

void decode(struct treeNode *root, char *inputFile, char *outputFile, struct treeNode *histogram);

/*!
 * \fn
 * \brief
 *
 * Mariusz
 */

void asciiToBin(unsigned char c, unsigned char *buffer, struct treeNode *histogram);

/*!
 * \fn
 * \brief
 *
 * Maciek
 */

void removeTree(struct treeNode *root);

#endif //tree.h
