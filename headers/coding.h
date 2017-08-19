#ifndef CODING_H
#define CODING_H

#include "../headers/argument.h"

extern struct treeNode *histogram;

/*!
 * \fn encode(char *input, char *outputFile, struct treeNode *histogram, int *codeCollision)
 * \brief Funkcja kodująca
 *
 * \param char *inputFile - nazwa pliku wejściowego
 * \param char *outputFile - nazwa pliku wyjściowego
 * \param struct treeNode *histogram - tablica histogramu
 * \param int *codeCollision - informacja o podwójnej reprezentacji ostatniego znaku
 * \return double - poziom kopresji jako stosunek rozmiaru pliku wyjściowego do wejściowego
 *
 * Funkcja pobiera z pliku wejściowego znak, znajduje jego kod w tablicy int **codes i zapisuje
 * do buffera unsigned char [9]. Jeśli kod nie wypełni wszystkich pól buffera, pobierany
 * jest następny znak. Jeśli buffer jest pełny jest on zamieniany na kod ASCII i zapisywany do pliku
 * wyjściowego. Pętla trwa aż do pobrania wszystkich znaków z pliku wejściowego.
 *
 */

double encode(char *input, char *outputFile, struct treeNode *histogram, int *codeCollision, enum argument arg);

/*!
 * \fn unsigned char binToAscii(unsigned char *binary, struct treeNode *histogram, int *codeCollision)
 * \brief Funkcja zamieniająca kody binarne na znaki ASCII
 *
 * \param unsigned char *binary - tablica z ośmio-bitową liczbą binarną
 * \param struct treeNode *histogram - tablica histogramu, z której pobierana jest wartość
 * histogram[].zeroes - zmienna zawierajaca ilość zer do wypełnienia w znaku
 * \param int *codeCollision - wkaźnik na zmienną zawierającą ilość zer w przypadku wystąpienia niezgodności
 * przy ostatnim znaku, gdy zakodowany kod jest dłuższy niż 1 bajt, a ostani znak można zapisać
 * przy użyciu mniej niż 8 bitów.
 * \return unsigned char - znak w kodzie ASCII
 *
 * Funkcja zamienia kod binarny na kod ASCII zapisując przy tym informację
 * o ilości zer do wypełnienia w polu 'zeroes' histogramu, oraz o podwójnej
 * reprezentacji o ile wystąpiła. W przypadku nie wystąpienia sytuacji z
 * podwójną reprezentacją jej wartość pozostaje domyślna (-1).
 */

unsigned char binToAscii(unsigned char *binary, struct treeNode *histogram, int *codeCollision);

/*!
 * \fn void generateKey(struct treeNode *histogram, char *outputFile, int codeCollision)
 * \brief Generacja klucza do dekodowania
 *
 * \param struct treeNode *histogram - tablica histogramu
 * \param char *outputFile - ścieżka do zakodowanego pliku, na podstawie której
 * generowany jest plik z kluczem
 * \param int codeCollision - informacja o podwójnej reprezentacji, która
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

void generateKey(struct treeNode *histogram, char *outputFile, int codeCollision);

/*!
 * \fn void keyToHistogram(char *key, struct treeNode *histogram, int *codeCollision)
 * \brief Funkcja odczytujaca klucz i zamieniajaca go na histogram
 *
 * \param char *key - klucz do odkodowania
 * \param struct treeNode *histogram - tablica histogramu
 * \param int *codeCollision - informacja o podwójnej reprezentacji.
 *
 * Funkcja pobierając kolejne tokeny z klucza tworzy histogram potrzebny
 * do zdekodowania pliku, oraz zapisuje informację o podwójnej reprezentacji.
 */

void keyToHistogram(char *key, struct treeNode *histogram, int *codeCollision);

/*!
 * \fn void decode(struct treeNode *root, char *inputFile, char *outputFile, struct treeNode *histogram, int *codeCollision)
 * \brief Funkcja dekodująca
 *
 * \param struct treeNode *root - wskaźnik na korzeń drzewa
 * \param char *inputFile - nazwa pliku wejściowego
 * \param char *outputFile - nazwa pliku wyjściowego
 * \param struct treeNode *histogram - tablica histogramu
 * \param int *codeCollision - informacja o podwójnej reprezentacji ostatniego znaku
 *
 * Funkcja pobiera z zakodowanego pliku wejściowego znak ASCII, zamienia go do postaci binarnej, po czym
 * przeszukuje drzewo zgodnie z bitami liczby binarnej (0 - w lewo, 1 - w prawo), aż do znalezienia liścia.
 * Jeśli został znaleziony liść, jego pole c zostaje zapisane do pliku wyjściowego, a wskaźnik drzewa zostaje
 * ustawiony na korzeń. Jeśli cały buffer z liczbą binarną został odczytany, zostaje pobrany kolejny znak
 * z pliku wejściowego i zamieniany do postaci binarnej. Jeśli natomiast odczytany jest ostatni znak, i pole
 * codeCollision jest różne od -1, to jego zawartość jest wpisywana w pole zer dla pobranego znaku.
 */

void decode(struct treeNode *root, char *inputFile, char *outputFile, struct treeNode *histogram, int *codeCollision);

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

#endif