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
 * Strukura bazowa pojedynczego węzła drzewa. Wykorzystywana do generowania
 * drzewa oraz histogramu.
 */

struct treeNode {
  unsigned char c; /**< kod ASCII znaku */
  int freq; /**< ilość wystąpień danego znaku */
  int zeroes; /**< ilośc zer do wypełnienia przy zamianie kodu ASCII bo kodu binarnego */
  struct treeNode *left; /**< adres lewego potomka węzła */
  struct treeNode *right; /**< adres prawego potomka węzła */
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
 * występujących w histogramie
 */

extern char **codes;

/*!
 * \fn bool createHistogram(char *inputFile, struct treeNode *histogram)
 * \brief Funkcja tworząca histogram
 *
 * Funkcja przyjmuje dwa parametry: char *inputFile - nazwa pliku wejściowego,
 * struct treeNode *histogram - tablica typu strukturalnego z informacjami
 * o danym znaku, ilości jego wystąpień i liczbie zer do wypełnienia dla kodu.
 * Zwraca wartość bool zależną od powodzenia działania funkcji.
 */

bool createHistogram(char *inputFile, struct treeNode *histogram);

/*!
 * \fn void quickSort(struct treeNode *histogram, int begin, int end)
 * \brief Funkcja sortująca histogram
 *
 * Funkcja przyjmuje trzy parametry: struct treeNode *histogram - tablica do posortowania
 * int begin - początkowy kraniec sortowania
 * int end - koñcowy kraniec sortowania
 *
 * Funkcja sortuje rosnąco po kodach ASCII znaków.
 */

 void quickSortChar(struct treeNode *histogram, int begin, int end);

 /*!
 * \fn void quickSort(struct treeNode *histogram, int begin, int end)
 * \brief Funkcja sortująca histogram
 *
 * Funkcja przyjmuje trzy parametry: struct treeNode *histogram - tablica do posortowania
 * int begin - początkowy kraniec sortowania
 * int end - koñcowy kraniec sortowania
 *
 * Funkcja sortuje malejąco po ilości wystąpień danego znaku.
 */

 void quickSortFreq(struct treeNode *histogram, int begin, int end);

/*!
 * \fn struct treeNode* generateTree(struct treeNode *root, struct treeNode *histogram)
 * \brief Funkcja tworząca drzewo na powstawie histogramu.
 *
 * Funkcja przyjmuje wskaźnik na korzeń drzewa i tablicę histogramu posortowaną
 * malejąco po ilościach wystąpień. W pierwszym kroku znajduje ostatni element
 * histogramu mający ilość wystąpień większą od zera. Następnie pobiera ten element
 * oraz element przedostatni, tworzy dla nich węzły i rodzica i szuka drzewa, do
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
 * Funkcja przyjmuje dwa parametry: struct list_pointers *list - wskaźnik na pierwszy element listy
 * struct treeNode *root - wskaźnik na korzeń drzewa
 * Funkcja przechodzi rekurencyjnie przez drzewo i z każdym wywołaniem tworzy nowy element listy,
 * do którego zapisuje 0 lub 1 w zależności od kierunku przechodzenia przez drzewo (0 - w lewo, 1 - w prawo),
 * aż do dojścia do liścia gdzie wywoływana jest funkcja saveCode().
 */

void createCodes(struct list_pointers *list, struct treeNode *root);

/*!
 * \fn saveCode(struct list_pointers *list, unsigned char c)
 * \brief Zapis kodu dla danego znaku do tablicy kodów
 *
 * Fukcja przyjmuje dwa parametry: wskaźnik na listę, oraz znak ASCII. Przy wywołaniu
 * spisuje kod z buffera, którym jest lista i zapisuje go do tablicy int **codes, przydzielając
 * przy dym pamięć dynamicznie.
 */

void saveCode(struct list_pointers *list, unsigned char c);

/*!
 * \fn void createList(struct list_pointers *list)
 * \brief Funkcja tworząca listę
 *
 * Funkcja przyjmuje strukturę wskaźników na listę.
 * Tworzy pierwszy element listy i ustawia wskaźniki head i tail na nowo powstały element, oraz
 * wskaźniki next i prev na NULL.
 */

void createList(struct list_pointers *list);

/*!
 * \fn insertListNode(struct list_pointers *list)
 * \brief Dodanie elementu do listy
 *
 * Jeśli lista nie jest pusta, funkcja dodaje nowy element listy do jej czoła.
 */

void insertListNode(struct list_pointers *list);

/*!
 * \fn void deleteListNode(struct list_pointers **list)
 * \brief Funkcja usuwająca element listy
 *
 * Mariusz
 * Funkcja przyjmuje podówójny wskaźnik na listę.
 * Usuwa ostatnio dodany do listy element pod warunkiem, że lista nie jest
 * pusta.
 */

void deleteListNode(struct list_pointers **list);

/*!
 * \fn encode(char *input, char *outputFile, struct treeNode *histogram, int *double_representation)
 * \brief Funkcja kodująca
 *
 * Fukncja przyjmuje 4 parametry.
 * char *inputFile - plik wejściowy
 * char *outputFile - plik wyjściowy
 * struct treeNode *histogram - histogram
 * int *double_representation - informacja o podwójnej reprezentacji ostatniego znaku
 *
 * Funkcja pobiera z pliku wejściowego znak, znajduje jego kod w teblicy int **codes i zapisuje
 * do buffera (tablica dziewięcio elementowa). Jeśli kod nie wypełni wszystkich pól buffera, pobierany
 * jest następny znak. Jeśli buffer jest pełny jest on zamieniany na kod ASCII i zapisywany do pliku
 * wyjściowego. Pętla trwa aż do pobrania wszystkich znaków z pliku wejściowego.
 * Funkcja zwraca poziom kopresji jako stosunek rozmiaru wyjściowego do wejściowego w formacie
 * double.
 */

double encode(char *input, char *outputFile, struct treeNode *histogram, int *double_representation);

/*!
 * \fn unsigned char binToAscii(unsigned char *array, struct treeNode *histogram, int *double_representation)
 * \brief Funkcja zamieniająca kody binarne na znaki ASCII
 *
 * Funkcja przyjmuje trzy parametry: unsigned char *array - tablica z ośmio-bitową liczbą binarną
 * struct treeNode *histogram - zmienna zawierajaca ilość zer w znaku
 * int *double_representation - zmienna zawierająca ilość zer w przypadku wystąpienia niezgodności
 * przy ostatnim znaku, gdy zakodowany kod jest dłuższy niż 1 bajt, a ostani znak można zapisać
 * przy użyciu mniej niż 8 bitów.
 * Funkcja zwraca gotowy znak ASCII w formacie unsigned char
 */

unsigned char binToAscii(unsigned char *array, struct treeNode *histogram, int *double_representation);

/*!
 * \fn generateKey(struct treeNode *histogram, int double_representation)
 * \brief Generacja klucza do dekodowania
 *
 * Funcja generuje klucz w formacie %dr:%c:%f:%z:%c:%f:%z... gdzie:
 * %dr - informacja o podwójnej reprezentacji ostatniego znaku
 * %c - znak ASCII
 * %f - ilośc wystąpień danego znaku
 * %z - ilość zer dla danego kodu
 *
 * Klucz jest wymagany do odkodowania uprzednio zakodowanego pliku.
 */

void generateKey(struct treeNode *histogram, int double_representation);

/*!
 * \fn void keyToHistogram(char *key, struct treeNode *histogram, int *double_representation)
 * \brief Funkcja odczytujaca klucz i zamieniajaca go na histogram
 *
 * Funkcja przyjmuje trzy parametry: char *key - klucz do odkodowania
 * struct treeNode *histogram - histogram
 * int *double_representation - informacja o podwójnej reprezentacji.
 * Funkcja pobierając kolejne tokeny z klucza tworzy histogram potrzebny
 * do zdekodowania pliku, oraz zapisuje informacje o podwójnej reprezentacji
 */

void keyToHistogram(char *key, struct treeNode *histogram, int *double_representation);

/*!
 * \fn void decode(struct treeNode *root, char *inputFile, char *outputFile, struct treeNode *histogram, int *double_representation)
 * \brief Funkcja dekodująca
 *
 * Fukncja przyjmuje 5 parametrów.
 * struct treeNode *root - korzeń drzewa
 * char *inputFile - plik wejściowy
 * char *outputFile - plik wyjściowy
 * struct treeNode *histogram - histogram
 * int *double_representation - informacja o podwójnej reprezentacji ostatniego znaku
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
 * \fn void asciiToBin(unsigned char c, unsigned char *buffer, struct treeNode *histogram, int *double_representation)
 * \brief Funkcja zamieniajaca pobrany z pliku znak ASCII na kod binarny
 *
 * Funkcja przyjmuje trzy parametry: unsigned char c - znak pobrany z pliku wejściowego
 * unsigned char *buffer - buffer na kod binarny
 * struct treeNode *histogram - histogram
 * Celem funkcji jest zamiana kodu zakodowanego w postaci kodów ASCII na kod binarny. Uzupełnia ona również kod
 * zerami zgodnie z polem histogram[c].zeroes.
 */

void asciiToBin(unsigned char c, unsigned char *buffer, struct treeNode *histogram);

/*!
 * \fn removeTree(struct treeNode *root)
 * \brief Funkcja usuwająca drzewo
 *
 * Funkcja przyjmuje wskaźnik na korzeń drzewa. Przechodzi je ona rekurencyjnie usuwając wszystkie wężły.
 */

void removeTree(struct treeNode *root);

#endif //tree.h
