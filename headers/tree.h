#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*!
 * \struct treeNode
 * \brief Struktura wêz³a drzewa
 *
 * Strukura zawiera pola c dla kodowanego znaku, freq dla iloœci jej wyst¹pieñ,
 * zeroes, wykorzystywan¹ do zapisu iloœci zer w kodach znaków i pola wska¿nikowe
 * left i right dla potomstwa danego wêz³a.
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
 * Zawiera pole code przechowuj¹ce znak '0' lub '1' w zale¿noœci od kierunku
 * odwiedzania wêz³ów
 */

struct list_node {
  char code;
  struct list_node *prev, *next;
};

/*!
 * \struct list_pointers
 * \brief Struktura wskaŸników do listy
 *
 * Tworzymy listê dwustronn¹, abt u³atwiæ odczyt kodów
 */

struct list_pointers {
  struct list_node *head, *tail;
};

/*!
 * \var char **codes
 * \brief Kody ka¿dego ze znaków
 *
 * Tablica wskaŸników na tablice zawieraj¹ce kody dla znaków ascii
 * wystêpuj¹cych w histogramie
 */

extern char **codes;

/*!
 * \fn bool createHistogram(char *inputFile, struct treeNode *histogram)
 * \brief Funkcja tworz¹ca histogram
 *
 * Funkcja przyjmuje dwa parametry: char *inputFile - nazwa pliku wejœciowego,
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
 * \brief Funkcja sortuj¹ca histogram
 *
 * Funkcja przyjmuje cztery parametry: struct treeNode *histogram - tablica do posortowania
 * int begin - pocz¹tkowy kraniec sortowania
 * int end - koñcowy kraniec sortowania
 * int type - znienna przyjmujaca 0 lub 1 w zaleznosci co sortujemy (0 - int freq, 1 - unsigned char c)
 */

int *getHistogram(struct treeNode *histogram, int i, int type);

/*!
 * \fn struct treeNode* generateTree(struct treeNode *root, struct treeNode *histogram)
 * \brief
 *
 * Maciek
 */

struct treeNode* generateTree(struct treeNode *root, struct treeNode *histogram);

/*!
 * \fn void createCodes(struct list_pointers *list, struct treeNode *root)
 * \brief Funkcja generujaca kody dla ka¿dego znaku
 *
 * Funkcja przyjmuje dwa parametry: struct list_pointers *list - wskaŸnik na pierwszy element listy
 * struct treeNode *root - wskaŸnik na korzeñ drzewa
 * Funkcja przechodzi rekurencyjnie przez drzewo i z ka¿dym wywo³aniem dopisuje 0 lub 1 do
 * nowego elementu listy, a¿ do dojœcia do koñca drzewa gdzie wywo³ywana jest funkcja saveCode
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
 * \brief Funkcja towrz¹ca liste
 *
 * Mariusz
 * Funkcja przyjmuje wskaŸnik na liste ?
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
 * \brief Funkcja usuwaj¹ca element listy
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

double encode(char *input, char *outputFile, struct treeNode *histogram, int *double_representation);

/*!
 * \fn unsigned char binToAscii(unsigned char *array, struct treeNode *histogram)
 * \brief Funkcja zamieniaj¹ca kody binarne na znaki ASCII
 *
 * Mariusz
 * Funkcja przyjmuje dwa parametry: unsigned char *array - tablica 8 kodow binarnych
 * struct treeNode *histogram - zmienna zawierajaca ilosc zer w znaku
 * Funkcja zwraca gotowy znak ASCII
 */

unsigned char binToAscii(unsigned char *array, struct treeNode *histogram, int *double_representation);

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

void decode(struct treeNode *root, char *inputFile, char *outputFile, struct treeNode *histogram, int *double_representation);

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
