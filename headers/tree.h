#ifndef TREE_H
#define TREE_H

#include <stdbool.h>
#include "../headers/list.h"
#include "../headers/argument.h"
#include "../headers/histogram.h"

#define ASCII_TABLE_SIZE 256
#define NUMBER_OF_NODES 2
#define CODE_LEFT '0'
#define CODE_RIGHT '1'
#define BYTE_SIZE 8
#define IS_ASCII(c)  ((c & ~0xFF) == 0)

/*!
 * \struct treeNode
 * \brief Struktura węzła drzewa
 *
 * Strukura bazowa pojedynczego węzła drzewa. Wykorzystywana do generowania
 * drzewa oraz histogramu.
 */

struct treeNode {
  unsigned char c; /*!< kod ASCII znaku */
  int freq; /*!< ilość wystąpień danego znaku */
  int zeroes; /*!< ilośc zer do wypełnienia przy zamianie kodu ASCII bo kodu binarnego */
  struct treeNode *left; /*!< adres lewego potomka węzła */
  struct treeNode *right; /*!< adres prawego potomka węzła */
};

/*!
 * \var char **codes
 * \brief Kody każdego ze znaków
 *
 * Tablica wskaźników na tablice zawierające kody dla znaków ascii
 * występujących w histogramie.
 */

extern char **codes;

/*!
 * \fn struct treeNode* generateTree(struct treeNode *root, struct treeNode *histogram)
 * \brief Funkcja tworząca drzewo na powstawie histogramu.
 *
 * \param struct treeNode *root - adres korzenia drzewa
 * \param struct treeNode *histogram - tablica histogramu
 * \return struct treeNode * - adres korzenia wygenerowanego drzewa.
 *
 * Funkcja przyjmuje wskaźnik na korzeń drzewa i tablicę histogramu posortowaną
 * malejąco po ilościach wystąpień. W pierwszym kroku znajduje ostatni element
 * histogramu mający ilość wystąpień większą od zera. Następnie pobiera ten element
 * oraz element przedostatni, tworzy dla nich węzły i rodzica, a następnie szuka drzewa, do
 * którego mogłaby podłączyć powstałe drzewo. Jeśli znajdzie wskaźnik na drzewo,
 * funcja złączy te drzewa tworząc nowego rodzica, którego lewy wskaźnik wskazuje
 * na nowo powstałe drzewo, a prawy na drzewo, do którego chcemy się podłączyć.
 * Adres nowego rodzica ustawia jako korzeń i pobiera dwa kolejne elementy
 * z histogramu, aż do wykorzystania wszystkich elementów. Jeśli jednak fukcja
 * nie znajdzie drzewa, do którego mogłaby połączyć nowo powstałe drzewo to ustawia
 * korzeń na nowo powstałe drzewo i pobiera kolejne elementy z histogramu.
 * Funkcja zwraca wskaźnik na korzeń wygenerowanego w ten sposób drzewa.
 */

struct treeNode* generateTree(struct treeNode *root, struct treeNode *histogram);

/*!
 * \fn void createCodes(struct list_pointers *list, struct treeNode *root)
 * \brief Funkcja generujaca kody dla każdego znaku
 *
 * \param struct treeNode *root - wskaźnik na korzeń drzewa
 * \param struct list_pointers *list - wskaźnik do struktury wskaźników na listę
 *
 * Funkcja przechodzi rekurencyjnie przez drzewo i z każdym wywołaniem tworzy nowy element listy,
 * do którego zapisuje 0 lub 1 w zależności od kierunku przechodzenia przez drzewo (0 - w lewo, 1 - w prawo),
 * aż do dojścia do liścia gdzie wywoływana jest funkcja saveCode().
 */

void createCodes(struct treeNode *root, struct listPointers *list);

/*!
 * \fn saveCode(struct list_pointers *list, unsigned char c)
 * \brief Zapis kodu dla danego znaku do tablicy kodów
 *
 * \param struct list_pointers *list - wskaźnik do struktury wskaźników na listę
 * \param unsigned char c -  znak ASCII
 *
 * Przy wywołaniu spisuje kod z buffera, którym jest lista i zapisuje go do
 * tablicy int **codes, przydzielając przy tym pamięć dynamicznie.
 */

void saveCode(struct listPointers *list, unsigned char c);

/*!
 * \fn removeTree(struct treeNode *root)
 * \brief Funkcja usuwająca drzewo
 *
 * \param removeTree(struct treeNode *root) - wskaźnik na korzeń drzewa.
 *
 * Funkcja przechodzi rekurencyjnie przez drzewo usuwając wszystkie wężły i
 * ustawiając adresy węzłów na NULL.
 */

void removeTree(struct treeNode *root);

bool isLeaf(struct treeNode *root);

bool isSingleLeafTree(struct treeNode *root, struct listPointers *list);

#endif
