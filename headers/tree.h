#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define ASCII_TABLE_SIZE 256
#define NUMBER_OF_NODES 2

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
 * \struct list_node
 * \brief Typ bazowy listy dwukierunkowej
 *
 * Wykorzystywana jako bufer do zapisu kodów przy przechodzeniu przez drzewo.
 */

struct list_node {
  char code; /**< Pole zawierające kod '0' bądz '1' zależności od kierunku
                  przechodzenia przez drzewo */
  struct list_node *prev; /**< Adres poprzedniego elementu listy */
  struct list_node *next; /**< Adres następnego elementu listy */
};

/*!
 * \struct list_pointers
 * \brief Struktura wskaźników do listy
 *
 * Tworzymy listę dwustronną, aby ułatwić odczyt kodów.
 */

struct list_pointers {
  struct list_node *head; /**< Adres czoła listy */
  struct list_node *tail; /**< Adres ogona listy */
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
 * \fn bool createHistogram(char *inputFile, struct treeNode *histogram)
 * \brief Funkcja tworząca histogram
 *
 * \param char *inputFile - nazwa pliku wejściowego,
 * \param struct treeNode *histogram  - tablica typu strukturalnego z informacjami
 * o danym znaku, ilości jego wystąpień i liczbie zer do wypełnienia dla kodu.
 * \return Wartość bool zależną od powodzenia działania funkcji.
 *
 * Funkcja generuje histogram zliczając ilość wystąpień danego znaku w
 * pliku wejściowym i zapisuje tą informację do tablicy histogramu.
 */

bool createHistogram(char *inputFile, struct treeNode *histogram);

/*!
 * \fn void quickSortChar(struct treeNode *histogram, int begin, int end)
 * \brief Funkcja sortująca histogram
 *
 * \param struct treeNode *histogram - tablica do posortowania
 * \param int begin - początkowy kraniec sortowania
 * \param int end - końcowy kraniec sortowania
 *
 * Funkcja sortuje rosnąco po kodach ASCII znaków celem ułatwienia znajdowania
 * danego znaku podczas generowania jego kodu.
 */

void quickSortChar(struct treeNode *histogram, int begin, int end);

 /*!
 * \fn void quickSortFreq(struct treeNode *histogram, int begin, int end)
 * \brief Funkcja sortująca histogram
 *
 * \param struct treeNode *histogram - tablica do posortowania
 * \param int begin - początkowy kraniec sortowania
 * \param int end - końcowy kraniec sortowania
 *
 * Funkcja sortuje malejąco po ilości wystąpień danego znaku. Wykorzystywana
 * do przygotowania histogramu przed generowaniem drzewa.
 */

void quickSortFreq(struct treeNode *histogram, int begin, int end);

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

void createCodes(struct list_pointers *list, struct treeNode *root);

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

void saveCode(struct list_pointers *list, unsigned char c);

/*!
 * \fn void createList(struct list_pointers *list)
 * \brief Funkcja tworząca listę
 *
 * \param struct list_pointers *list - wskaźnik do struktury wskaźników na listę
 *
 * Funkcja tworzy pierwszy element listy i ustawia wskaźniki head i tail na nowo powstały element, oraz
 * wskaźniki next i prev na NULL.
 */

void createList(struct list_pointers *list);

/*!
 * \fn insertListNode(struct list_pointers *list)
 * \brief Dodanie elementu do listy
 *
 * \param struct list_pointers *list - wskaźnik do struktury wskaźników na listę
 *
 * Jeśli lista nie jest pusta, funkcja dodaje nowy element listy do jej czoła.
 */

void insertListNode(struct list_pointers *list);

/*!
 * \fn void deleteListNode(struct list_pointers **list)
 * \brief Funkcja usuwająca element listy
 *
 * \param struct list_pointers **list - podwójny wskaźnik do struktury wskaźników
 * na listę
 *
 * Funckja usuwa ostatnio dodany do listy element pod warunkiem, że lista nie jest
 * pusta.
 */

void deleteListNode(struct list_pointers **list);

/*!
 * \fn encode(char *input, char *outputFile, struct treeNode *histogram, int *double_representation)
 * \brief Funkcja kodująca
 *
 * \param char *inputFile - nazwa pliku wejściowego
 * \param char *outputFile - nazwa pliku wyjściowego
 * \param struct treeNode *histogram - tablica histogramu
 * \param int *double_representation - informacja o podwójnej reprezentacji ostatniego znaku
 * \return double - poziom kopresji jako stosunek rozmiaru pliku wyjściowego do wejściowego
 *
 * Funkcja pobiera z pliku wejściowego znak, znajduje jego kod w tablicy int **codes i zapisuje
 * do buffera unsigned char [9]. Jeśli kod nie wypełni wszystkich pól buffera, pobierany
 * jest następny znak. Jeśli buffer jest pełny jest on zamieniany na kod ASCII i zapisywany do pliku
 * wyjściowego. Pętla trwa aż do pobrania wszystkich znaków z pliku wejściowego.
 *
 */

double encode(char *input, char *outputFile, struct treeNode *histogram, int *double_representation);

/*!
 * \fn unsigned char binToAscii(unsigned char *binary, struct treeNode *histogram, int *double_representation)
 * \brief Funkcja zamieniająca kody binarne na znaki ASCII
 *
 * \param unsigned char *binary - tablica z ośmio-bitową liczbą binarną
 * \param struct treeNode *histogram - tablica histogramu, z której pobierana jest wartość
 * histogram[].zeroes - zmienna zawierajaca ilość zer do wypełnienia w znaku
 * \param int *double_representation - wkaźnik na zmienną zawierającą ilość zer w przypadku wystąpienia niezgodności
 * przy ostatnim znaku, gdy zakodowany kod jest dłuższy niż 1 bajt, a ostani znak można zapisać
 * przy użyciu mniej niż 8 bitów.
 * \return unsigned char - znak w kodzie ASCII
 *
 * Funkcja zamienia kod binarny na kod ASCII zapisując przy tym informację
 * o ilości zer do wypełnienia w polu 'zeroes' histogramu, oraz o podwójnej
 * reprezentacji o ile wystąpiła. W przypadku nie wystąpienia sytuacji z
 * podwójną reprezentacją jej wartość pozostaje domyślna (-1).
 */

unsigned char binToAscii(unsigned char *binary, struct treeNode *histogram, int *double_representation);

/*!
 * \fn void generateKey(struct treeNode *histogram, char *outputFile, int double_representation)
 * \brief Generacja klucza do dekodowania
 *
 * \param struct treeNode *histogram - tablica histogramu
 * \param char *outputFile - ścieżka do zakodowanego pliku, na podstawie której
 * generowany jest plik z kluczem
 * \param int double_representation - informacja o podwójnej reprezentacji, która
 * zapisywana jest do pliku z kluczem
 *
 * Funcja generuje klucz w formacie %dr:%c:%f:%z:%c:%f:%z... gdzie:
 * %dr - informacja o podwójnej reprezentacji ostatniego znaku
 * %c - znak ASCII
 * %f - ilośc wystąpień danego znaku
 * %z - ilość zer dla danego kodu
 * Nazwa pliku z kluczem jest to nazwa pliku zakodowanego z dopiskiem "_key"
 * Klucz jest wymagany do odkodowania uprzednio zakodowanego pliku.
 */

void generateKey(struct treeNode *histogram, char *outputFile, int double_representation);

/*!
 * \fn void keyToHistogram(char *key, struct treeNode *histogram, int *double_representation)
 * \brief Funkcja odczytujaca klucz i zamieniajaca go na histogram
 *
 * \param char *key - klucz do odkodowania
 * \param struct treeNode *histogram - tablica histogramu
 * \param int *double_representation - informacja o podwójnej reprezentacji.
 *
 * Funkcja pobierając kolejne tokeny z klucza tworzy histogram potrzebny
 * do zdekodowania pliku, oraz zapisuje informację o podwójnej reprezentacji.
 */

void keyToHistogram(char *key, struct treeNode *histogram, int *double_representation);

/*!
 * \fn void decode(struct treeNode *root, char *inputFile, char *outputFile, struct treeNode *histogram, int *double_representation)
 * \brief Funkcja dekodująca
 *
 * \param struct treeNode *root - wskaźnik na korzeń drzewa
 * \param char *inputFile - nazwa pliku wejściowego
 * \param char *outputFile - nazwa pliku wyjściowego
 * \param struct treeNode *histogram - tablica histogramu
 * \param int *double_representation - informacja o podwójnej reprezentacji ostatniego znaku
 *
 * Funkcja pobiera z zakodowanego pliku wejściowego znak ASCII, zamienia go do postaci binarnej, po czym
 * przeszukuje drzewo zgodnie z bitami liczby binarnej (0 - w lewo, 1 - w prawo), aż do znalezienia liścia.
 * Jeśli został znaleziony liść, jego pole c zostaje zapisane do pliku wyjściowego, a wskaźnik drzewa zostaje
 * ustawiony na korzeń. Jeśli cały buffer z liczbą binarną został odczytany, zostaje pobrany kolejny znak
 * z pliku wejściowego i zamieniany do postaci binarnej. Jeśli natomiast odczytany jest ostatni znak, i pole
 * double_representation jest różne od -1, to jego zawartość jest wpisywana w pole zer dla pobranego znaku.
 */

void decode(struct treeNode *root, char *inputFile, char *outputFile, struct treeNode *histogram, int *double_representation);

/*!
 * \fn void asciiToBin(unsigned char c, unsigned char *buffer, struct treeNode *histogram)
 * \brief Funkcja zamieniajaca pobrany z pliku znak ASCII na kod binarny
 *
 * \param unsigned char c - znak pobrany z pliku wejściowego
 * \param unsigned char *buffer - buffer na kod binarny
 * \param struct treeNode *histogram - tablica histogramu
 *
 * Celem funkcji jest zamiana kodu zakodowanego w postaci kodów ASCII na kod binarny. Uzupełnia ona również kod
 * zerami zgodnie z polem histogram[c].zeroes.
 */

void asciiToBin(unsigned char c, unsigned char *buffer, struct treeNode *histogram);

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

#endif //tree.h
