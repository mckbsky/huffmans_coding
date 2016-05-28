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
 * \fn bool createHistogram(char *inputFile, struct treeNode *histogram)
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
 * \fn void quickSort(struct treeNode *histogram, int begin, int end, int type)
 * \brief Funkcja sortująca histogram
 *
 * Funkcja przyjmuje cztery parametry: struct treeNode *histogram - tablica do posortowania
 * int begin - początkowy kraniec sortowania
 * int end - końcowy kraniec sortowania
 * int type - znienna przyjmujaca 0 lub 1 w zaleznosci co sortujemy (0 - int freq, 1 - unsigned char c)
 */

long *getHistogram(struct treeNode *histogram, int i, int type);

/*!
 * \fn struct treeNode* generateTree(struct treeNode *root, struct treeNode *histogram)
 * \brief
 *
 * Maciek
 */

struct treeNode* generateTree(struct treeNode *root, struct treeNode *histogram);

/*!
 * \fn void createCodes(struct list_pointers *list, struct treeNode *root)
 * \brief Funkcja generujaca kody dla każdego znaku
 *
 * Funkcja przyjmuje dwa parametry: struct list_pointers *list - wskaźnik na pierwszy element listy
 * struct treeNode *root - wskaźnik na korzeń drzewa
 * Funkcja przechodzi rekurencyjnie przez drzewo i z każdym wywołaniem dopisuje 0 lub 1 do
 * nowego elementu listy, aż do dojścia do końca drzewa gdzie wywoływana jest funkcja saveCode
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
 * \fn void createList(struct list_pointers *list)
 * \brief Funkcja towrząca liste
 *
 * Mariusz
 * Funkcja przyjmuje wskaźnik na liste ?
 * Tworzenie pierwszego elemtnu listy
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
 * \fn void deleteListNode(struct list_pointers **list)
 * \brief Funkcja usuwająca element listy
 *
 * Mariusz
 * Funkcja przyjmuje ??
 * Usuwanie ostatnio dodanego elementu listy
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
 * \fn unsigned char binToAscii(unsigned char *array, struct treeNode *histogram)
 * \brief Funkcja zamieniająca kody binarne na znaki ASCII
 *
 * Mariusz
 * Funkcja przyjmuje dwa parametry: unsigned char *array - tablica 8 kodow binarnych
 * struct treeNode *histogram - zmienna zawierajaca ilosc zer w znaku
 * Funkcja zwraca gotowy znak ASCII
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
 * \fn void keyToHistogram(char *key, struct treeNode *histogram)
 * \brief Funkcja odczytujaca klucz i zamieniajaca go na histogram
 *
 * Mariusz
 * Funkcja przyjmuje dwa parametry: char *key - klucz do odkodowania
 * struct treeNode *histogram - tablica
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
 * \fn void asciiToBin(unsigned char c, unsigned char *buffer, struct treeNode *histogram)
 * \brief Funkcja zamieniajaca pobrany z pliku znak ASCII na kody binarne
 *
 * Mariusz
 * Funkcja przyjmuje trzy parametry: unsigned char c - znak pobrany z pliku binarnego
 * unsigned char *buffer - tablica 8 kodow binarnych ??
 * struct treeNode *histogram - tablica ??
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
