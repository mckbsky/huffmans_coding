#ifndef QUICKSORT_H
#define QUICKSORT_H
#include "../headers/tree.h"

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

#endif