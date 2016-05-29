#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*!
 * \struct treeNode
 * \brief Struktura w�z�a drzewa
 *
 * Strukura zawiera pola c dla kodowanego znaku, freq dla ilo�ci jej wyst�pie�,
 * zeroes, wykorzystywan� do zapisu ilo�ci zer w kodach znak�w i pola wska�nikowe
 * left i right dla potomstwa danego w�z�a.
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
 * Wykorzystywana jako bufer do zapisu kod�w przy przechodzeniu przez drzewo.
 * Zawiera pole code przechowuj�ce znak '0' lub '1' w zale�no�ci od kierunku
 * odwiedzania w�z��w
 */

struct list_node {
  char code;
  struct list_node *prev, *next;
};

/*!
 * \struct list_pointers
 * \brief Struktura wska�nik�w do listy
 *
 * Tworzymy list� dwustronn�, abt u�atwi� odczyt kod�w
 */

struct list_pointers {
  struct list_node *head, *tail;
};

/*!
 * \var char **codes
 * \brief Kody ka�dego ze znak�w
 *
 * Tablica wska�nik�w na tablice zawieraj�ce kody dla znak�w ascii
 * wyst�puj�cych w histogramie
 */

extern char **codes;

/*!
 * \fn bool createHistogram(char *inputFile, struct treeNode *histogram)
 * \brief Funkcja tworz�ca histogram
 *
 * Funkcja przyjmuje dwa parametry: char *inputFile - nazwa pliku wej�ciowego,
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
 * \brief Funkcja sortuj�ca histogram
 *
 * Funkcja przyjmuje cztery parametry: struct treeNode *histogram - tablica do posortowania
 * int begin - pocz�tkowy kraniec sortowania
 * int end - ko�cowy kraniec sortowania
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
 * \brief Funkcja generujaca kody dla ka�dego znaku
 *
 * Funkcja przyjmuje dwa parametry: struct list_pointers *list - wska�nik na pierwszy element listy
 * struct treeNode *root - wska�nik na korze� drzewa
 * Funkcja przechodzi rekurencyjnie przez drzewo i z ka�dym wywo�aniem dopisuje 0 lub 1 do
 * nowego elementu listy, a� do doj�cia do ko�ca drzewa gdzie wywo�ywana jest funkcja saveCode
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
 * \brief Funkcja towrz�ca liste
 *
 * Mariusz
 * Funkcja przyjmuje wska�nik na liste ?
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
 * \brief Funkcja usuwaj�ca element listy
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
 * \brief Funkcja zamieniaj�ca kody binarne na znaki ASCII
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
